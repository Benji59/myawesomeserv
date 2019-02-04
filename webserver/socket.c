#include <sys/net.h>

int creer_serveur ( int port ){

	int socket_serveur ;
	socket_serveur = socket (AF_INET , SOCK_STREAM , 0);

	if (socket_serveur == -1){
		/* traitement de l ’ erreur */
		perror ("socket_serveur ");
		return -1;
	}

	struct sockaddr_in saddr ;
	saddr.sin_family = AF_INET ; /* Socket ipv4 */
	saddr.sin_port = htons (8080); /* Port d ’é coute */
	saddr.sin_addr.s_addr = INADDR_ANY ; /* é coute sur toutes les interfaces */
	
	if (bind (socket_serveur , ( struct sockaddr *)&saddr , sizeof(saddr)) == -1){
		perror ("bind socker_serveur");/* traitement de l ’ erreur */
		return -1;
	}

	return socket_serveur;
}