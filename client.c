// The client side of The Marriage Hall Function Hall Booking & Food/Music Arrangment System
// To run the prgram change the ip address indicated in client
// to the ip adress of the host machine

// compile using gcc -o client client.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 4444

// Session cookies
char user_name_cookie[20] = "";



GtkWidget *welcome_page;
GtkWidget *user_btn;
GtkWidget *admin_btn;

GtkWidget *admin_authorization_page;
GtkWidget *admin_pas_val_label;
GtkWidget *admin_password_entry;
GtkWidget *admin_login_btn;
GtkWidget *admin_auth_back_btn;

GtkWidget *user_authorization_page;
GtkWidget *user_login_val_label;
GtkWidget *user_login_btn;
GtkWidget *user_register_btn;
GtkWidget *user_auth_back_btn;

GtkWidget *user_login_page;
GtkWidget *user_loginusername_entry;
GtkWidget *user_loginpassword_entry;
GtkWidget *user_login_in_login_page_btn;
GtkWidget *user_login_back_btn;

GtkWidget *admin_menu_page;
GtkWidget *admin_cancel_reservation_btn;
GtkWidget *admin_show_reservation_btn;
GtkWidget *admin_menu_back_btn; 

GtkWidget *user_menu_page;
GtkWidget *new_reservation_btn;
GtkWidget *cancel_reservation_btn;
GtkWidget *show_reservation_btn;
GtkWidget *user_menu_back_btn;

GtkWidget *user_register_page;
GtkWidget *user_registerusername_entry;
GtkWidget *user_registerpassword_entry;
GtkWidget *user_register_in_register_page_btn;
GtkWidget *user_register_back_btn;

GtkWidget *user_reservations_page;
GtkWidget *user_reservations_content_label;
GtkWidget *user_reservations_back_btn;

GtkWidget *user_cancel_reserv_page;
GtkWidget *user_cancel_content_label;
GtkWidget *user_cancel_entry;
GtkWidget *user_cancel_reservation_btn;
GtkWidget *user_cancel_back_btn;

GtkWidget *admin_reservations_page;
GtkWidget *admin_reservations_content_label;
GtkWidget *admin_reservations_back_btn;

GtkWidget *admin_cancel_reserv_page;
GtkWidget *admin_cancel_content_label;
GtkWidget *admin_cancel_entry;
GtkWidget *admin_cancel_reserv_by_id_btn;
GtkWidget *admin_cancel_back_btn;

GtkWidget *bookingsystem_page;
GtkWidget *theme_entry;
GtkWidget *entertainment_entry;
GtkWidget *day_entry;
GtkWidget *month_entry;
GtkWidget *food_entry;
GtkWidget *music_entry;
GtkWidget *apply_btn;
GtkWidget *booking_back_btn; 

int sock = 0;
int valread;
struct sockaddr_in serv_addr;
struct sockaddr_in address;
char buffer[1024] = {0};
char cchat[1024];

GtkBuilder *builder;

int main(int argc, char *argv[]) {
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//-------------Initializing sockets and related things -----------------------------------//
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	
	printf("CREATING CLIENT SOCKET .....\n");
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
		return -1;
	}
	printf("DEFINING CLIENT SOCKET FAMILY, ADDRESS & PORT .....\n");
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	printf("CLIENT CONNECTING ON PORT 8080 TO COMMUNICATE WITH SERVER.....\n");
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\nConnection Failed \n");
		return -1;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////
	
	send(sock, "hello", strlen("hello"), 0);
	printf("Hello message sent\n");
	
	valread = read(sock, buffer, 1024);
	printf("%s\n", buffer);
	
	memset(buffer, 0, sizeof(buffer));
  	memset(cchat, 0, sizeof(cchat));
	
	////////////////////////////////////////////////////////////////////////////////////////////


	
	
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//----------------------------------------------------------------------------------------//
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	
	
	gtk_init(&argc, &argv);
	
	builder = gtk_builder_new_from_file ("marriage.glade");
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Creating all the pages ========================================================= */
	////////////////////////////////////////////////////////////////////////////////////////////
	
	welcome_page = GTK_WIDGET(gtk_builder_get_object(builder, "welcome_page"));
	admin_authorization_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_authorization_page"));
	user_authorization_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_authorization_page"));
	user_login_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_page"));
	admin_menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_menu_page"));
	user_menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_menu_page"));
	user_register_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_page"));
	bookingsystem_page = GTK_WIDGET(gtk_builder_get_object(builder, "bookingsystem_page"));
	user_reservations_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_reservations_page"));
	user_cancel_reserv_page = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_reserv_page"));
	admin_reservations_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_reservations_page"));
	admin_cancel_reserv_page = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_reserv_page"));
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Positioning all the pages ====================================================== */
	////////////////////////////////////////////////////////////////////////////////////////////
	
	gtk_window_move(GTK_WINDOW(welcome_page), 700, 200);
	gtk_window_move(GTK_WINDOW(admin_authorization_page), 700, 250);
	gtk_window_move(GTK_WINDOW(user_authorization_page), 700, 250);
	gtk_window_move(GTK_WINDOW(user_login_page), 700, 250);
	gtk_window_move(GTK_WINDOW(admin_menu_page), 700, 250);
	gtk_window_move(GTK_WINDOW(user_menu_page), 700, 250);
	gtk_window_move(GTK_WINDOW(user_register_page), 700, 250);
	gtk_window_move(GTK_WINDOW(bookingsystem_page), 700, 150);
	gtk_window_move(GTK_WINDOW(user_reservations_page), 400, 150);
	gtk_window_move(GTK_WINDOW(user_cancel_reserv_page), 400, 150);
	gtk_window_move(GTK_WINDOW(admin_reservations_page), 400, 150);
	gtk_window_move(GTK_WINDOW(admin_cancel_reserv_page), 400, 150);
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== If x is pressed on any page the program exits ////////////////////////////////// */
	////////////////////////////////////////////////////////////////////////////////////////////
	
	g_signal_connect(welcome_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(admin_authorization_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(user_authorization_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(user_login_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(admin_menu_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(user_menu_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(user_register_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(bookingsystem_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(user_reservations_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(user_cancel_reserv_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(admin_reservations_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(admin_cancel_reserv_page, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_builder_connect_signals(builder, NULL);
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Creating the buttons =========================================================== */
	////////////////////////////////////////////////////////////////////////////////////////////
	
	// Welcome page btns
	user_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_btn")); 
	admin_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_btn"));
	
	// Admin Auth page btns
	admin_login_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_login_btn")); 
	admin_auth_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_auth_back_btn"));
	
	// User Auth page btns
	user_login_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_btn")); 
	user_register_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_btn"));
	user_auth_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_auth_back_btn"));
	
	// User Login page btns
	user_login_in_login_page_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_in_login_page_btn"));
	user_login_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_back_btn"));
	
	// Admin Menu page btns
	admin_cancel_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_reservation_btn"));
	admin_show_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_show_reservation_btn"));
	admin_menu_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_menu_back_btn"));
	
	// User Menu page btns
	new_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "new_reservation_btn"));
	cancel_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_reservation_btn"));
	show_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "show_reservation_btn"));
	user_menu_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_menu_back_btn"));
	
	// User Register page btns
	user_register_in_register_page_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_in_register_page_btn"));
	user_register_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_register_back_btn"));
	
	// Booking System page btns
	apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "apply_btn"));
	booking_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "booking_back_btn"));
	
	// User Reservations page btns
	user_reservations_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_reservations_back_btn"));
	
	// User Reservations Cancel page btns
	user_cancel_reservation_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_reservation_btn"));
	user_cancel_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_back_btn"));
	
	// Admin Reservations page btns
	admin_reservations_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_reservations_back_btn"));
	
	// Admin Reservations Cancel page btns
	admin_cancel_reserv_by_id_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_reserv_by_id_btn"));
	admin_cancel_back_btn = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_back_btn"));
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Creating the entries =========================================================== */
	////////////////////////////////////////////////////////////////////////////////////////////
	
	// Admin Auth page entry
	admin_password_entry = GTK_WIDGET(gtk_builder_get_object(builder, "admin_password_entry"));

	// User Login page entries
	user_loginusername_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_loginusername_entry"));
	user_loginpassword_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_loginpassword_entry"));
	
	// User Register page entries
	user_registerusername_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_registerusername_entry"));
	user_registerpassword_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_registerpassword_entry"));
	
	// Booking System page entries
	theme_entry = GTK_WIDGET(gtk_builder_get_object(builder, "theme_entry"));
	entertainment_entry = GTK_WIDGET(gtk_builder_get_object(builder, "entertainment_entry"));
	day_entry = GTK_WIDGET(gtk_builder_get_object(builder, "day_entry"));
	month_entry = GTK_WIDGET(gtk_builder_get_object(builder, "month_entry"));
	food_entry = GTK_WIDGET(gtk_builder_get_object(builder, "food_entry"));
	music_entry = GTK_WIDGET(gtk_builder_get_object(builder, "music_entry"));
	
	// User Reservations Cancel page entry
	user_cancel_entry = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_entry"));
	
	// Admin Reservations Cancel page enty
	admin_cancel_entry = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_entry"));
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Creating the labels ============================================================ */
	////////////////////////////////////////////////////////////////////////////////////////////
	
	// User Authorization page label
	user_login_val_label = GTK_WIDGET(gtk_builder_get_object(builder, "user_login_val_label"));
	
	// Admin Authorization page label
	admin_pas_val_label = GTK_WIDGET(gtk_builder_get_object(builder, "admin_pas_val_label"));
	
	// User Reservations page label
	user_reservations_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "user_reservations_content_label"));
	
	// User Reservations Cancel page label
	user_cancel_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "user_cancel_content_label"));
	
	// Admin Reservations page label
	admin_reservations_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "admin_reservations_content_label"));
	
	// Admin Reservations Cancel page label
	admin_cancel_content_label = GTK_WIDGET(gtk_builder_get_object(builder, "admin_cancel_content_label"));
	
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	//----------------------------------------------------------------------------------------//
	////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////
	gtk_widget_show(welcome_page);
	gtk_main();
	
	return EXIT_SUCCESS;
	}
	
	
	// x Welcome page 
	// x Admin Auth page
	// x User Auth page
	// x User Login page 
	// x Admin Menu page 
	// x User Menu page 
	// x User Register page
	// x Booking System page
	// x User Reservations page
	// x User Reservations Cancel page
	// x Admin Reservations page btns
	// x Admin Reservations Cancel page
	
	
	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Welcome Page functions ========================================================= */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_user_btn_clicked (GtkButton *b) {
	gtk_widget_hide(welcome_page);
	
	gtk_widget_show(user_authorization_page);
}

void on_admin_btn_clicked (GtkButton *b) {
	gtk_widget_hide(welcome_page);
	
	gtk_widget_show(admin_authorization_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Admin Authorization Page functions ============================================= */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_admin_login_btn_clicked (GtkButton *b) {
	char password[9];
	
	sprintf(password, "%s", gtk_entry_get_text(GTK_ENTRY(admin_password_entry)));
	
	if(strcmp(password, "pass1234") == 0) {
		gtk_widget_hide(admin_authorization_page);
	
		gtk_widget_show(admin_menu_page);
	} else {
		gtk_label_set_text(GTK_LABEL(admin_pas_val_label), (const gchar*) "Wrong password!!!");
	}
	
	
}

void on_admin_auth_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(admin_authorization_page);
	
	gtk_widget_show(welcome_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////	
	/* ===== User Authorization Page functions ===============================================*/
	////////////////////////////////////////////////////////////////////////////////////////////
void on_user_login_btn_clicked (GtkButton *b) {
	gtk_widget_hide(user_authorization_page);
	
	gtk_widget_show(user_login_page);
}	
	
void on_user_register_btn_clicked (GtkButton *b) {
	
	gtk_widget_hide(user_authorization_page);
	
	gtk_widget_show(user_register_page);
}

void on_user_auth_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(user_authorization_page);
	
	gtk_widget_show(welcome_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== User Login Page functions ====================================================== */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_user_login_in_login_page_btn_clicked (GtkButton *b) {
	char user_name[9];
	char password[9];
	char queryLoginValidate[100] = "queryLoginValidate/";
	
	sprintf(user_name, "%s", gtk_entry_get_text(GTK_ENTRY(user_loginusername_entry)));
	sprintf(password, "%s", gtk_entry_get_text(GTK_ENTRY(user_loginpassword_entry)));
	
	strcat(queryLoginValidate, user_name);
	strcat(queryLoginValidate, "/");
	strcat(queryLoginValidate, password);
	strcat(queryLoginValidate, "/");
	
	printf("%s\n", queryLoginValidate);
	send(sock, queryLoginValidate, strlen(queryLoginValidate), 0);
	int i=0;
	
	//do {
		memset(buffer, 0, sizeof(buffer));
		
		sleep(2);
		
		valread = read(sock, buffer, 1024);
		
		printf("\nBuffer=%s\n", buffer);
		
		if(strcmp("Wrong", buffer) == 0) {
			gtk_label_set_text(GTK_LABEL(user_login_val_label), (const gchar*) "Wrong password!!!");
		} else {
			strcpy(user_name_cookie, user_name);
			i++;
			gtk_widget_hide(user_login_page);
	
			gtk_widget_show(user_menu_page);
		}
		
		memset(buffer, 0, sizeof(buffer));
		//strcmp("Right", buffer);	
	//}while(i == 0);
	//gtk_widget_show(user_login_page);
	
	
}

void on_user_login_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(user_login_page);
	
	gtk_widget_show(user_authorization_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== Admin Menu Page ================================================================ */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_admin_cancel_reservation_btn_clicked (GtkButton *b) {
	char queryReservationsAll[100] = "queryReservationsAll/";
	send(sock, queryReservationsAll, strlen(queryReservationsAll), 0);
	
	memset(buffer, 0, sizeof(buffer));
	sleep(2);
	
	valread = read(sock, buffer, 1024);
	
	gtk_label_set_text(GTK_LABEL(admin_cancel_content_label), buffer);

	gtk_widget_hide(admin_menu_page);
	
	gtk_widget_show(admin_cancel_reserv_page);
}

void on_admin_show_reservations_btn_clicked (GtkButton *b) {
	char queryReservationsAll[100] = "queryReservationsAll/";
	send(sock, queryReservationsAll, strlen(queryReservationsAll), 0);
	
	memset(buffer, 0, sizeof(buffer));
	sleep(2);
	
	valread = read(sock, buffer, 1024);
	
	gtk_label_set_text(GTK_LABEL(admin_reservations_content_label), buffer);
	
	
	gtk_widget_hide(admin_menu_page);
	
	gtk_widget_show(admin_reservations_page);
}

void on_admin_menu_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(admin_menu_page);
	
	gtk_widget_show(admin_authorization_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////
	/* ===== User Menu Page ================================================================= */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_new_reservation_btn_clicked (GtkButton *b) {
	

	gtk_widget_hide(user_menu_page);
	
	gtk_widget_show(bookingsystem_page);
}	
	
void on_cancel_reservation_btn_clicked (GtkButton *b) {
	
	char queryUserReservations[100] = "queryUserReservations/";
	strcat(queryUserReservations, user_name_cookie);
	strcat(queryUserReservations, "/");
	
	send(sock, queryUserReservations, strlen(queryUserReservations), 0);
	
	memset(buffer, 0, sizeof(buffer));
	sleep(2);
	
	valread = read(sock, buffer, 1024);
	
	gtk_label_set_text(GTK_LABEL(user_cancel_content_label), buffer);
	
	gtk_widget_hide(user_menu_page);
	
	gtk_widget_show(user_cancel_reserv_page);
}	
	
void on_show_reservations_btn_clicked (GtkButton *b) {
	char queryUserReservations[500] = "queryUserReservations/";
	strcat(queryUserReservations, user_name_cookie);
	strcat(queryUserReservations, "/");
	
	printf("%s\n", queryUserReservations);
	
	send(sock, queryUserReservations, strlen(queryUserReservations), 0);
	
	sleep(2);
	
	memset(buffer, 0, 1024);
	valread = read(sock, buffer, 1024);
	
	
	printf("\nBuffer=%s", buffer);
	gtk_label_set_text(GTK_LABEL(user_reservations_content_label), buffer);
	
	gtk_widget_hide(user_menu_page);
	
	gtk_widget_show(user_reservations_page);
	memset(buffer, 0, 1024);
}

void on_user_menu_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(user_menu_page);
	
	gtk_widget_show(user_login_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////	
	/* ===== User Register Page ============================================================= */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_user_register_in_register_page_btn_clicked (GtkButton *b) {
	char user_name[9];
	char password[9];
	char queryNewUser[100] = "queryNewUser/";

	sprintf(user_name, "%s", gtk_entry_get_text(GTK_ENTRY(user_registerusername_entry)));
	sprintf(password, "%s", gtk_entry_get_text(GTK_ENTRY(user_registerpassword_entry)));
	
	printf("%s\n", user_name);
	printf("%s\n", password);
	strcat(queryNewUser, user_name);
	strcat(queryNewUser, "/");
	strcat(queryNewUser, password);
	strcat(queryNewUser, "/");
	
	printf("%s\n", queryNewUser);
	send(sock, queryNewUser, strlen(queryNewUser), 0);
	
	gtk_widget_hide(user_register_page);
	
	gtk_widget_show(user_authorization_page);
}

void on_user_register_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(user_register_page);
	
	gtk_widget_show(user_authorization_page);
}
	
	////////////////////////////////////////////////////////////////////////////////////////////	
	/* ===== Booking System Page ============================================================ */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_apply_btn_clicked (GtkButton *b) {
	char theme[32];
	char entertainment[32];
	char day[32];
	char month[32];
	char food[32];
	char music[32];
	char queryNewReservation[300];

  	memset(theme, 0, 32);
  	memset(entertainment, 0, 32);
  	memset(day, 0, 32);
  	memset(month, 0, 32);
  	memset(food, 0, 32);
  	memset(music, 0, 32);
	memset(queryNewReservation, 0, 300);
	
	strcpy(queryNewReservation, "queryNewReservation/");
	//char date[9];
	
	sprintf(theme, "%s", gtk_entry_get_text(GTK_ENTRY(theme_entry)));
	sprintf(entertainment, "%s", gtk_entry_get_text(GTK_ENTRY(entertainment_entry)));
	
	sprintf(day, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(day_entry)));
	sprintf(month, "%d", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(month_entry)));
	
	sprintf(music, "%s", gtk_entry_get_text(GTK_ENTRY(music_entry)));
	sprintf(food, "%s", gtk_entry_get_text(GTK_ENTRY(food_entry)));

	strcat(queryNewReservation, user_name_cookie);
	strcat(queryNewReservation, "/");
	strcat(queryNewReservation, theme);
	strcat(queryNewReservation, "/");
	strcat(queryNewReservation, entertainment);
	strcat(queryNewReservation, "/");
	strcat(queryNewReservation, day);
	strcat(queryNewReservation, "/");
	strcat(queryNewReservation, month);
	strcat(queryNewReservation, "/");
	strcat(queryNewReservation, food);
	strcat(queryNewReservation, "/");
	strcat(queryNewReservation, music);
	strcat(queryNewReservation, "/");
	
	printf("%s\n", queryNewReservation);
	
	send(sock, queryNewReservation, strlen(queryNewReservation), 0);
	
	sleep(1);
	
	gtk_widget_hide(bookingsystem_page);
	
	
	gtk_widget_show(user_reservations_page);
}

void on_booking_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(bookingsystem_page);
	
	gtk_widget_show(user_menu_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////	
	/* ===== User Reservations Page ========================================================= */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_user_reservations_back_btn_clicked (GtkButton *b) {

	gtk_widget_hide(user_reservations_page);
	
	gtk_widget_show(user_menu_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////	
	/* ===== User Reservations Cancel Page ================================================== */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_user_cancel_reservation_btn_clicked (GtkButton *b) {
	char user_id[12];
	char queryUserCancelReserv[100] = "queryUserCancelReserv/";
	
	sprintf(user_id, "%s", gtk_entry_get_text(GTK_ENTRY(user_cancel_entry)));
	
	strcat(queryUserCancelReserv, user_id);
	strcat(queryUserCancelReserv, "/");
	
	printf("%s\n", queryUserCancelReserv);
	
	send(sock, queryUserCancelReserv, strlen(queryUserCancelReserv), 0);
	
	
}

void on_user_cancel_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(user_cancel_reserv_page);
	
	gtk_widget_show(user_menu_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////	
	/* ===== Admin Reservations Page ======================================================== */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_admin_reservations_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(admin_reservations_page);
	
	gtk_widget_show(admin_menu_page);
}

	////////////////////////////////////////////////////////////////////////////////////////////	
	/* ===== Admin Reservations Cancel Page ================================================= */
	////////////////////////////////////////////////////////////////////////////////////////////
void on_admin_cancel_back_btn_clicked (GtkButton *b) {
	gtk_widget_hide(admin_cancel_reserv_page);
	gtk_widget_show(admin_menu_page);
}


void on_admin_cancel_reserv_by_id_btn_clicked (GtkButton *b) {
	char reserv_id[10];
	
	sprintf(reserv_id, "%s", gtk_entry_get_text(GTK_ENTRY(admin_cancel_entry)));
	
	printf("%s\n", reserv_id);
	
	char queryUserCancelReserv[100] = "queryUserCancelReserv/";
	strcat(queryUserCancelReserv, reserv_id);
	strcat(queryUserCancelReserv, "/");
	
	printf("%s\n", queryUserCancelReserv);
	
	send(sock, queryUserCancelReserv, strlen(queryUserCancelReserv), 0);
	
	sleep(2);
	
	gtk_widget_hide(admin_cancel_reserv_page);
	//on_admin_show_reservations_btn_clicked(b);
	gtk_widget_show(admin_cancel_reserv_page);
}