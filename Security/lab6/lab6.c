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

#define CAFILE "/etc/ssl/certs/ca-certificates.crt" //path to CAfile 
#define CADIR "/etc/ssl/certs/" //CAdirectory
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

	if (SSL_CTX_load_verify_locations(ctx, CAFILE,CADIR) !=1)
	printf ("Error loading CAfile and or dir\n");

	if (!SSL_CTX_set_default_verify_paths (ctx)) {
        fprintf(stderr, "SSL_CTX_set_default_verify_paths failed\n");
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
	 
	 SSL_set_cipher_list(ssl, "DEFAULT:!TLS_AES_256_GCM_SHA384"); //in case of TSL1.2
	 SSL_set_ciphersuites(ssl, "TLS_CHACHA20_POLY1305_SHA256:TLS_AES_128_GCM_SHA256:TLS_AES_128_CCM_8_SHA256:TLS_AES_128_CCM_SHA256");//in case of TSL1.3 ; in this list excluded the first used cipher (TLS_AES_256_GCM_SHA384); 
	
	if( !SSL_set_fd(ssl,sockfd) ) {
		fprintf(stderr, "SSL_set_fd  failed\n");
		exit(1); }
	
	if(SSL_connect(ssl) <= 0 ) {
		fprintf(stderr, "SSL_set_fd  failed\n");
		exit(1); }
	
	X509 * cert = SSL_get_peer_certificate(ssl);
	if (!ssl) {
		fprintf (stderr, "SSL_get_peer_certificate failed\n");
		exit (1);}	
	
/* printing out part of certificate , verifying result*/
	char subj[BUFSIZE+1];
	char issuer[BUFSIZE+1];

	X509_NAME_oneline(X509_get_subject_name(cert), subj, BUFSIZE);
	X509_NAME_oneline(X509_get_issuer_name(cert), issuer, BUFSIZE);
	printf("certificate chain: %s\n", subj);
	printf("issuer: %s\n\n", issuer);
	

     	int err = SSL_get_verify_result(ssl);
		if (err != X509_V_OK) {
		const char *message = X509_verify_cert_error_string(err);
                fprintf(stderr,"Cert verification error: %s (%d)\n", message, err); 
		exit (1);
		} else {  printf ("\nX509_V_OK: ok\n\n"); }


/* open and write to certfile */ 
	FILE * fc = fopen(certfile,"wb");
	if (!fc) {
		fprintf (stderr, "Failed to open cert.pem file\n");
		exit (1);}

	if( !PEM_write_X509(fc,cert) ) {
		fprintf (stderr, "PEM_write_X509 failed\n");
		exit (1);}
		fclose(fc);	

	char buffer[BUFSIZE] = HTTP_REQUEST;
			
	if (SSL_write(ssl, buffer, strlen(buffer)) <= 0){	
		fprintf(stderr, "SSL_write failed\n");}
		//exit(1); }
// Open and write the content of webpage	
	int datalen = 0;
	FILE * fOutput = fopen(outfile,"wb");
	while( (res = SSL_read(ssl,buffer,BUFSIZE)) > 0 )	
	{
		fwrite(buffer,sizeof(char),res,fOutput);
		datalen += res;
	}

	const SSL_CIPHER * cipher = SSL_get_current_cipher (ssl);
	printf("Used cipher: %s\n" , SSL_CIPHER_get_name (cipher)); 
	printf("TLS = Cipher Suite\nCHACHA20 POLY1305 = ChaCha stream cipher,Poly1305 authenticator)\nSHA256 = Secure Hash Algorithm 256\n\n");
	printf("TLS_AES_256_GCM_SHA384 cipher were used before excluding it by not including this cipher in SSL_set_ciphersuites\n\n");



	int count = 0;
	const char * cipher_List;
	const char *SSL_get_cipher_list(const SSL *ssl, int priority);
	
	while ((cipher_List = SSL_get_cipher_list (ssl,count)) != NULL)
	 {
		printf("cipher_List = %s \n" , cipher_List);
		count++;
	 }
	

	fclose(fOutput);
	SSL_shutdown(ssl);
	close(sockfd);
	SSL_free(ssl);
	SSL_CTX_free(ctx);

	return 0;
}


