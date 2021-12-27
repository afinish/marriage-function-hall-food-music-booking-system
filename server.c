// The server side of The Marriage Hall Function Hall Booking & Food/Music Arrangment System
// To run the prgram change the ip address indicated in this program
// to the ip adress of the host machine

// compile using gcc -o server $(mysql_config --cflags) server.c $(mysql_config --libs)

#include <stdbool.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 4444

// MySQL variables for connection 
static char *host = "localhost";
static char *user = "root";
static char *pass = "password1D.";
static char *dbname = "test";

// MySQL initialization variables
MYSQL *con;
//MYSQL_RES *res;
//MYSQL_ROW row;

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0;

/*
// Sockets initialization variables
int sockfd, ret;
struct sockaddr_in serverAddr;//
int newSocket;//
struct sockaddr_in newAddr;//
socklen_t addr_size;
char buffer[1024];//*/
pid_t childpid;
	
struct sockaddr_in serverAddr;
struct sockaddr_in address;

int server_fd;
int sock; 
int valread;
int opt = 1;
int addrlen = sizeof(address);
char buffer[1024] = { 0 };
char schat[1024];
socklen_t addr_size;

int main(int argc, char const *argv[]) {
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//-------------Initializing the Mysql database -------------------------------------------//
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	
	con = mysql_init(NULL);
	
	if(!(mysql_real_connect(con, host, user, pass, dbname, port, unix_socket, flag))) 
	{
		fprintf(stderr, "\nError: %s [%d] \n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//-------------Initializing sockets and related things -----------------------------------//
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	
	printf("CREATING SERVER SOCKET .....\n");
	server_fd = socket(AF_INET, SOCK_STREAM, 0);

	if (server_fd < 0) {	
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	/*
	printf("DEFINING SERVER SOCKET OPTIONS, FAMILY, ADDRESS & PORT .....\n");
	setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
		perror("setsockopt failed");
		exit(EXIT_FAILURE);
	}*/
	
	address.sin_family = AF_INET;
	//address.sin_addr.s_addr = INADDR_ANY;
	
	address.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("192.168.153.123");
	printf("BINDING SERVER SOCKET TO PORT 8080 .....\n");
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)	{	
		perror("socket bind failed");
		exit(EXIT_FAILURE);
	}
	printf("SERVER LISTENING ON PORT 8080 FOR NEW CONNECTION.....\n");
	if (listen(server_fd, 3) < 0){
		perror("sockeet listen failed ");
		exit(EXIT_FAILURE);
	}
	/*
	if ((sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
		perror("socket accept failed");
		exit(EXIT_FAILURE);
	}*/
	printf("SERVER ACCEPTED NEW CONNECTION FROM A CLIENT ON PORT 8080 .....\n");
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/*
	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);
	
	send(sock, "hello", strlen("hello"), 0);
	printf(" Ready for Chat....\n");
	
	memset(buffer, 0, sizeof(buffer));
  	memset(schat, 0, sizeof(schat));
	*/
	////////////////////////////////////////////////////////////////////////////////////////////

	while(1) {
		//if ((sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
		//	perror("socket accept failed");
		//	exit(EXIT_FAILURE);
		//}
		sock = accept(server_fd, (struct sockaddr *)&address, &addr_size);
		if(socket < 0) {
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
		
		if((childpid =fork()) == 0) {
			close(server_fd);
			
			while(1) {
				recv(sock, buffer, 1024, 0);
				if(strcmp(buffer, ":exit") == 0){
					printf("Disconnected from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
					break;
				}else{
					printf("Client: %s\n", buffer);
					send(sock, buffer, strlen(buffer), 0);
					bzero(buffer, sizeof(buffer));
					
					while(1) {
					memset(buffer, 0, sizeof(buffer));
  		valread = read(sock, buffer, 1024);
  		char query[100];
  		
  		strcpy(query, buffer);
  		
  		int i=0;
  		
  		
  		while(buffer[i++] != '/');
  		buffer[i-1] = '\0';
  		
  		printf("%s\n", buffer);
  		printf("%s\n", buffer);
  		
  		if(strcmp(buffer, "queryNewUser") == 0) {
  			printf("1\n");
  			printf("%s\n", query);
  			
  			char user_name[20];
  			char password[20];
  			
  			int n1=0, n2=0, n3=0;
  			for(int i=0; i<strlen(query); i++) {
  				if(query[i] == '/') {
  					if(n1 == 0) n1 = i;
  					else if(n2 == 0) n2 = i;
  					else if(n3 == 0) n3 = i;
  				}
  			}
  			memset(user_name, 0, 20);
  			memset(password, 0, 20);
  			
  			strncpy(user_name, query+n1+1, n2-n1-1);
  			strncpy(password, query+n2+1, n3-n2-1);
  			user_name[strlen(user_name)] = '\0';
  			password[strlen(password)] = '\0';
  			
  			
  			printf("\nnew_user_name=%s\npassword=%s\n", user_name, password);
  			
  			char sqlQuery[500] = "insert into users (user_name, password) values ('";
  			strcat(sqlQuery, user_name);
			strcat(sqlQuery, "\', \'");
			strcat(sqlQuery, password);
			strcat(sqlQuery, "\');");
  			
  			//printf("%s\n", sqlQuery);
  			
  			mysql_query(con, sqlQuery);
  		} else if(strcmp(buffer, "queryLoginValidate") == 0) {
  			printf("2\n");
  			char user_name[20];
  			char password[20];
  			
  			int n1=0, n2=0, n3=0;
  			for(int l=0; l<strlen(query); l++) {
  				if(query[l] == '/') {
  					if(n1 == 0) n1 = l;
  					else if(n2 == 0) n2 = l;
  					else if(n3 == 0) n3 = l;
  				}
  			}
  			
  			memset(user_name, 0, 20);
  			memset(password, 0, 20);
  			strncpy(user_name, query+n1+1, n2-n1-1);
  			strncpy(password, query+n2+1, n3-n2-1);
  			user_name[strlen(user_name)] = '\0';
  			password[strlen(password)] = '\0';
  			
  			printf("\nuser_name=%s\npassword=%s\n", user_name, password);
  			
  			MYSQL_RES *res;
  			MYSQL_ROW row;
  			
  			char sqlQueryUser[500] = "select user_name from users where user_name='";
			strcat(sqlQueryUser, user_name);
			strcat(sqlQueryUser, "\';");
			
			printf("\nuserQuery='%s\n", sqlQueryUser);
			//strcat(user_name, password);
  			mysql_query(con, sqlQueryUser);
  			
  			res = mysql_store_result(con);
  			
  			char user_name_db[20];
  			while(row = mysql_fetch_row(res)) {
				sprintf(user_name_db, "%s", (const char*) row[0]);
			}
			
			mysql_free_result(res);
			
			char sqlQueryPass[500] = "select password from users where password='";
			strcat(sqlQueryPass, password);
			strcat(sqlQueryPass, "\';");
			
  			printf("\npasswordQuery='%s\n", sqlQueryPass);
  			
  			mysql_query(con, sqlQueryPass);
  			
  			res = mysql_store_result(con);
  			
  			char password_db[20];
  			while(row = mysql_fetch_row(res)) {
  				sprintf(password_db, "%s", (const char*) row[0]);
  			}
  			
  			printf("\n%s == %s\n%s == %s\n", user_name_db, user_name, password_db, password);
  			
  			printf("\nn1=%d\n", strcmp(user_name_db, user_name));
  			printf("\nn2=%d\n", strcmp(password_db, password));
  			
  			if(strcmp(user_name_db, user_name) == 0 &&
  				strcmp(password_db, password) == 0) {
  				
  				send(sock, "Right", strlen("Right"), 0);
  			} else {
  				send(sock, "Wrong", strlen("Wrong"), 0);
  			}
  			
  		} else if(strcmp(buffer, "queryUserCancelReserv") == 0) {
  			printf("3\n");
  			char reserv_id[12];
  			memset(reserv_id, 0, 12);
  			int n1=0, n2=0;
  			for(int l=0; l<strlen(query); l++) {
  				if(query[l] == '/') {
  					if(n1 == 0) n1 = l;
  					else if(n2 == 0) n2 = l;
  				}
  			}
  			
  			strncpy(reserv_id, query+n1+1, n2-n1-1);
  			reserv_id[strlen(reserv_id)] = '\0';
  			
  			printf("\nreserv_id=%s\n", reserv_id);
  			
  			char sqlQuery[500] = "delete from reserv where reserv_id='";
  			strcat(sqlQuery, reserv_id);
  			strcat(sqlQuery, "\';");
  			
  			printf("%s\n", sqlQuery);
  			
  			mysql_query(con, sqlQuery);
  			
  		} else if(strcmp(buffer, "queryUserReservations") == 0) {
  			printf("4\n");//
  			/*char allReserv[100] = "select * from reserv";
  			MYSQL_RES *res;
  			MYSQL_ROW row;
  			
  			mysql_query(con, allReserv);
  			
  			res = mysql_store_result(con);
  			
  			char labelText[2048] = ".";
  			while(row = mysql_fetch_row(res)) {
  			//id user	Theme		Entertainment		Day Month	Food			Music
  				strcat(labelText, row[0]);
  				strcat(labelText, "\t");
  				strcat(labelText, row[1]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[2]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[3]);
  				strcat(labelText, "\t\t\t");
  				strcat(labelText, row[4]);
  				strcat(labelText, "\t");
  				strcat(labelText, row[5]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[6]);
  				strcat(labelText, "\t\t\t");
  				strcat(labelText, row[7]);
  				strcat(labelText, "\t\t\t\n");
  				
  				
  				//sprintf(labelText, "%s\t%s\t\t%s\t\t%s %s\t%s\t\t\t%s\t\t\t\n", row[0]
  			}
  			printf("\nSend=%s", labelText);
  			send(sock, labelText, strlen(labelText), 0);*/
  			
  			char user_name[20];
  			memset(user_name, 0, 20);
  			 
  			int n1=0, n2=0;
  			for(int l=0; l<strlen(query); l++) {
  				if(query[l] == '/') {
  					if(n1 == 0) n1 = l;
  					else if(n2 == 0) n2 = l;
  				}
  			}
  			
  			strncpy(user_name, query+n1+1, n2-n1-1);
  			user_name[strlen(user_name)] = '\0';
  			
  			printf("\nUser name=%s\n", user_name);
  			
  			char userReserv[500];
  			memset(userReserv, 0, 500);
  			strcpy(userReserv, "select * from reserv where user_name='");
  			
  			strcat(userReserv, user_name);
  			strcat(userReserv, "\';");
  			
  			MYSQL_RES *res;
  			MYSQL_ROW row;
  			
  			mysql_query(con, userReserv);
  			
  			res = mysql_store_result(con);
  			
  			char labelText[2048] = ".";
  			while(row = mysql_fetch_row(res)) {
  			//id user	Theme		Entertainment		Day Month	Food			Music

  				strcat(labelText, row[0]);
  				strcat(labelText, "\t");
  				strcat(labelText, row[1]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[2]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[3]);
  				strcat(labelText, "\t\t\t");
  				strcat(labelText, row[4]);
  				strcat(labelText, "\t");
  				strcat(labelText, row[5]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[6]);
  				strcat(labelText, "\t\t\t");
  				strcat(labelText, row[7]);
  				strcat(labelText, "\t\t\t\n");
  				
  				
  				//sprintf(labelText, "%s\t%s\t\t%s\t\t%s %s\t%s\t\t\t%s\t\t\t\n", row[0]
  			}
  			printf("\nSend=%s", labelText);
  			send(sock, labelText, strlen(labelText), 0);
  			
  			} else if(strcmp(buffer, "queryReservationsAll") == 0) {
  			printf("5\n");
  			char allReserv[100] = "select * from reserv";
  			MYSQL_RES *res;
  			MYSQL_ROW row;
  			
  			mysql_query(con, allReserv);
  			
  			res = mysql_store_result(con);
  			
  			char labelText[2048] = ".";
  			while(row = mysql_fetch_row(res)) {
  			//id user	Theme		Entertainment		Day Month	Food			Music
  				strcat(labelText, row[0]);
  				strcat(labelText, "\t");
  				strcat(labelText, row[1]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[2]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[3]);
  				strcat(labelText, "\t\t\t");
  				strcat(labelText, row[4]);
  				strcat(labelText, "\t");
  				strcat(labelText, row[5]);
  				strcat(labelText, "\t\t");
  				strcat(labelText, row[6]);
  				strcat(labelText, "\t\t\t");
  				strcat(labelText, row[7]);
  				strcat(labelText, "\t\t\t\n");
  				
  				
  				//sprintf(labelText, "%s\t%s\t\t%s\t\t%s %s\t%s\t\t\t%s\t\t\t\n", row[0]
  			}
  			printf("\nSend=%s", labelText);
  			send(sock, labelText, strlen(labelText), 0);
  			
  		} else if(strcmp(buffer, "queryNewReservation") == 0) {
  			printf("6\n");
  			printf("%s\n", query);

  			char user_name[20];
  			char theme[32];
  			char entertainment[32];
  			char day[32];
  			char month[32];
  			char food[32];
  			char music[32];
  			
  			memset(user_name, 0, 20);
  			memset(theme, 0, 32);
  			memset(entertainment, 0, 32);
  			memset(day, 0, 32);
  			memset(month, 0, 32);
  			memset(food, 0, 32);
  			memset(music, 0, 32);
  			
  			
  			int n1=0, n2=0, n3=0, n4=0, n5=0, n6=0, n7=0, n8=0;
  			
  			for(int i=0; i<strlen(query); i++) {
  				if(query[i] == '/') {
  					if(n1 == 0) n1 = i;
  					else if(n2 == 0) n2 = i;
  					else if(n3 == 0) n3 = i;
  					else if(n4 == 0) n4 = i;
  					else if(n5 == 0) n5 = i;
  					else if(n6 == 0) n6 = i;
  					else if(n7 == 0) n7 = i;
  					else if(n8 == 0) n8 = i;
  				}
  				//printf("%d\n", query[i]);
  			}
  			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", n1, n2, n3, n4, n5, n6, n7, n8);
  			strncpy(user_name, query+n1+1, n2-n1-1);
  			strncpy(theme, query+n2+1, n3-n2-1);
  			strncpy(entertainment, query+n3+1, n4-n3-1);
  			strncpy(day, query+n4+1, n5-n4-1);
  			strncpy(month, query+n5+1, n6-n5-1);
  			strncpy(food, query+n6+1, n7-n6-1);
  			strncpy(music, query+n7+1, n8-n7-1);

  			user_name[strlen(user_name)] = '\0';
  			theme[strlen(theme)] = '\0';
  			entertainment[strlen(entertainment)] = '\0';
  			day[strlen(day)] = '\0';
  			month[strlen(month)] = '\0';
  			food[strlen(food)] = '\0';
  			music[strlen(music)] = '\0';
  			
  			printf("%s\t%s\t%s\t%s\t%s\t%s\n", theme, entertainment, day, month, food, music);
  			
  			char sqlQuery[500];
  			memset(sqlQuery, 0, 500);
  			strcpy(sqlQuery, "insert into reserv(user_name, theme, entertainment, day, month, food, music) values ('");
  			
  			strcat(sqlQuery, user_name);
  			strcat(sqlQuery, "\', \'");
  			strcat(sqlQuery, theme);
  			strcat(sqlQuery, "\', \'");
  			strcat(sqlQuery, entertainment);
  			strcat(sqlQuery, "\', \'");
  			strcat(sqlQuery, day);
  			strcat(sqlQuery, "\', \'");
  			strcat(sqlQuery, month);
  			strcat(sqlQuery, "\', \'");
  			strcat(sqlQuery, food);
  			strcat(sqlQuery, "\', \'");
  			strcat(sqlQuery, music);
  			strcat(sqlQuery, "\'");
  			strcat(sqlQuery, ");");
  			
  			printf("\n%s\n", sqlQuery);
  			
  			mysql_query(con, sqlQuery);
  			
  		} else if(strcmp(buffer, "queryAdminCancel") == 0) {
  			
  		} else {
  			printf("0\n");
  		}
				}
			}
		}
		}
		//Client[clientCount].sockID = accept(serverSocket, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);
		//Client[clientCount].index = clientCount;
		
		//pthread_create(&thread[clientCount], NULL, doNetworking, (void *) &Client[clientCount]);
		
		//clientCount++;
	}


	return 0;
}

int queryLoginValidate(char* user_name, char* password) {
	char query[500] = "select * from users where user_name='";
	strcat(query, user_name);
	strcat(query, "\' and password='");
	strcat(query, password);
	strcat(query, "\';");
	strcat(user_name, password);
	//return executeQueryU(query);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void executeQuery(char* query) {
	printf("%s\n", query);
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;
	con = mysql_init(NULL);
	
	if(!(mysql_real_connect(con, host, user, pass, dbname, port, unix_socket, flag))) 
	{
		fprintf(stderr, "\nError: %s [%d] \n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	mysql_query(con, query);
  	mysql_query(con, "SELECT * FROM reservations");
	
	res = mysql_store_result(con);
	
	while(row = mysql_fetch_row(res)) {
		printf("%s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4]);
	}
	
	mysql_free_result(res);
	//return EXIT_SUCCESS;
}

int executeQueryU(char* query) {
	printf("%s\n", query);
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;
	con = mysql_init(NULL);
	
	if(!(mysql_real_connect(con, host, user, pass, dbname, port, unix_socket, flag))) 
	{
		fprintf(stderr, "\nError: %s [%d] \n", mysql_error(con), mysql_errno(con));
		exit(1);
	}
	
	mysql_query(con, query);
	
	res = mysql_store_result(con);
	char name_password[200] = "\0";
	
	while(row = mysql_fetch_row(res)) {
		printf("%s %s\n", row[1], row[2]);
		strcat(name_password, row[1]);
		strcat(name_password, row[2]);
	}
	printf("%s %ld\n", name_password, strlen(name_password));
	mysql_free_result(res);
	//return EXIT_SUCCESS;
	return strlen(name_password);
}