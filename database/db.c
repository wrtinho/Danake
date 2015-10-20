#include "db.h"

//Base de conhecimento sobre SQLite3: http://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm

//Variáveis globais usadas na classe db.C
sqlite3 *db;
sqlite3_stmt *stmt;
int msg;
char *MsgErro = 0;
char *sql;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int conecta_db(){

   int ret;

   ret = sqlite3_open("BancoDados.db", &db);

   if( ret ){
      fprintf(stderr, "Erro ao conectar com o banco de dados: %s\n", sqlite3_errmsg(db));
   }else{
      fprintf(stderr, "Conexão realizada com sucesso\n");
   }

   return(ret);
}

int criar_tabela(){
	int ret = 0;
	/* Create comando SQL */
   sql = "CREATE TABLE usuario("  \
         "id			 INT PRIMARY KEY NOT NULL AUTOINCREMENT," \
         "usuario        TEXT    NOT NULL," \
         "nome           TEXT    NOT NULL," \
         "aniversario    TEXT    NOT NULL," \
         "sexo			 TEXT    NOT NULL," \
		 "link           TEXT    NOT NULL," \
		 "email          TEXT    NOT NULL," \
		 "localizacao    TEXT    NOT NULL) ;";

   /* Execute SQL statement */
   ret = sqlite3_exec(db, sql, callback, 0, &MsgErro);
   if( ret != SQLITE_OK ){
	  fprintf(stderr, "SQL error: %s\n", MsgErro);
      sqlite3_free(MsgErro);
   }else{
      fprintf(stdout, "Tabela criada com sucesso\n");
   }
   encerra_conexao();
   return 1;
}

int insere_registro(usuario u) {

    int ret = conecta_db();

	sql = "INSERT INTO usuario(usuario, aniversario, link, nome, localizacao, sexo, email) VALUES(?, ?, ?, ?, ?, ?, ?, ?);";

    if (ret != SQLITE_OK) {

        fprintf(stderr, "Falha ao conectar no banco de dados: %s\n", sqlite3_errmsg(db));
        close_db();

        return 0;

        } else{

        msg = sqlite3_exec(db, sql, callback, 0, &MsgErro);
        if (msg != SQLITE_OK ) {

            fprintf(stderr, "SQL error: %s\n", MsgErro);
            close_db();

            return 0;
        } else {
                  sqlite3_bind_null(stmt, 1);
                  sqlite3_bind_text(stmt, 2, u.usuario, strlen(u.usuario), 0);
                  sqlite3_bind_text(stmt, 3, u.aniversario, strlen(u.aniversario), 0);
                  sqlite3_bind_text(stmt, 4, u.link, strlen(u.link), 0);
                  sqlite3_bind_text(stmt, 5, u.nome, strlen(u.nome), 0);
                  sqlite3_bind_text(stmt, 6, u.localizacao, strlen(u.localizacao), 0);
                  sqlite3_bind_text(stmt, 7, u.sexo, strlen(u.sexo), 0);
                  sqlite3_bind_text(stmt, 8, u.email, strlen(u.email), 0);
        }

        // commit
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        encerra_conexao();
        return 1;
    }
}

int atualiza_registro(usuario u) {
    sql = "UPDATE usuario SET aniversario = ?, link = ?, nome = ?, localizacao = ?, sexo = ?, email = ? WHERE usuario = ?;";

    int r = conecta();
    if (r != SQLITE_OK) {

        fprintf(stderr, "Falha ao conectar no banco de dados: %s\n", sqlite3_errmsg(db));
        encerra_conexao();

        return 0;

        }
	else{

        msg = sqlite3_exec(db, sql, callback, 0, &MsgErro);
        if (msg != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", MsgErro);
            encerra_conexao();

            return 0;
        }
		else {
            sqlite3_bind_text(stmt, 1, u.aniversario, strlen(u.aniversario), 0);
            sqlite3_bind_text(stmt, 2, u.link, strlen(u.link), 0);
            sqlite3_bind_text(stmt, 3, u.nome, strlen(u.nome), 0);
            sqlite3_bind_text(stmt, 4, u.localizacao, strlen(u.localizacao), 0);
            sqlite3_bind_text(stmt, 5, u.sexo, strlen(u.sexo), 0);
            sqlite3_bind_text(stmt, 6, u.email, strlen(u.email), 0);
            sqlite3_bind_text(stmt, 7, u.usuario, strlen(u.usuario), 0);
        }

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        encerra_conexao();
        return 1;
    }
}

int apaga_registro(usuario u) {

	sql = "DELETE FROM usuario WHERE usuario = ?;";

    int ret = dbect_db();
    if (ret != SQLITE_OK) {

        fprintf(stderr, "Falha ao conectar no banco de dados: %s\n", sqlite3_errmsg(db));
        encerra_conexao();

        return 0;

    } 
	else {
        msg = sqlite3_prepare(db, sql, -1, &stmt, 0);

        if (msg != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", MsgErro);
            encerra_conexao();

            return 0;

        } else {
            sqlite3_bind_text(stmt, 1,  u.usuario, strlen(u.usuario), 0);
        }

        encerra_conexao();
    }
    return 1;
}

int seleciona_registros() {
    sql = "SELECT * FROM usuario;";
    int ret = conecta();
	if (ret != SQLITE_OK) {
        
        fprintf(stderr, "Falha ao conectar no banco de dados: %s\n", sqlite3_errmsg(db));
        encerra_conexao();
		
        return 0;

    	}
	else{
        msg = sqlite3_exec(db, sql, callback, 0, &MsgErro);

		if (msg != SQLITE_OK ) {
		
            fprintf(stderr, "Erro ao realizar consulta no banco de dados\n");
            fprintf(stderr, "SQL error: %s\n", MsgErro);
			sqlite3_free(MsgErro);
            encerra_conexao();
		
            return 0;
        }
		
        encerra_conexao();
        return 1;
	}
}

void encerra_conexao() {
    sqlite3_free(MsgErro);
	sqlite3_close(db);
}