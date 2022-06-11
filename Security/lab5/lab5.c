#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>

#define BUFSIZE 1024
#define IP_ADDRESS "147.32.232.212"
#define HOSTNAME "fit.cvut.cz"
#define BUFF_SIZE 1024
#define HTTP_REQUEST  \
	"GET /en/student/forms HTTP/1.1\r\n"   \
	"Connection: close \r\n" \
	"Host: " HOSTNAME "\r\n\r\n"  


int main(int argc, char * argv[])
{
	if(argc != 3){
		fprintf(stderr, "Usage: %s cert.pem outfile ", argv[0]);
		exit(1);}


char *certfile = argv[1];
char *outfile =  argv[2];


	int sockfd;
	struct sockaddr_in servaddr;

	sockfd=socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(IP_ADDRESS); //ip address
	servaddr.sin_port=htons(443); // port

	if( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0 ) {
		fprintf(stderr, "Connection failed\n");
		exit(1);}
	
	SSL_library_init();
	
	SSL_CTX * ctx = SSL_CTX_new(SSLv23_method());
	if (NULL == ctx) {
		fprintf(stderr, "SSL_CTX_new (SSLv23_method)  failed\n");
		exit(1);}
	
	SSL_CTX_set_options(ctx,SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_TLSv1);
	
	SSL * ssl = SSL_new(ctx);
	if (NULL == ssl) {
		fprintf(stderr, "SSL_new  failed\n");
		exit(1); }

	int res = 0;
	res = SSL_set_tlsext_host_name(ssl, "fit.cvut.cz"); //SNI
	if (1!= res) {
		fprintf(stderr, "SSL_set_tlsext_host_name  failed\n");
		exit(1); }

	if( !SSL_set_fd(ssl,sockfd) ) {
		fprintf(stderr, "SSL_set_fd  failed\n");
		exit(1); }
	
	if(SSL_connect(ssl) <= 0 ) {
		fprintf(stderr, "SSL_connect  failed\n");
		exit(1); }
	
	X509 * cert = SSL_get_peer_certificate(ssl);
	if (!ssl) {
		fprintf (stderr, "SSL_get_peer_certificate failed");
		exit (1);}

/* open and write to certfile */ 
	FILE * fc = fopen(certfile,"wb");
	if (!fc) {
		fprintf (stderr, "Failed to open cert.pem file\n");
		exit (1);}
	res = PEM_write_X509(fc,cert);
	if( 1 != res) {
		fprintf (stderr, "PEM_write_X509 failed\n");
		exit (1);}
		fclose(fc);	

	char buffer[BUFSIZE] = HTTP_REQUEST;
			
	if (SSL_write(ssl, buffer, strlen(buffer)) <= 0){	
		fprintf(stderr, "SSL_write failed\n");
		exit(1); }
// Open and write the content of webpage	
	int datalen = 0;
	FILE * fOutput = fopen(outfile,"wb");
	while( (res = SSL_read(ssl,buffer,BUFSIZE)) > 0 )	
	{
		fwrite(buffer,res, sizeof(char),fOutput);
		datalen += res;
	}
	
	fclose(fOutput);



	SSL_shutdown(ssl);
	close(sockfd);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	
	
    printf("Ok\n");
    
	return 0;
}


