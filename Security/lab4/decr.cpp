//Sultanalieva Nuray, username: sultanur
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <string.h>
#include <iostream>
#define  BUFSIZE 1024


int main (int argc, char *argv[]) {

	if (argc != 4) {
		fprintf(stderr, "Usage: %s ct_infile privkey.pem outfile\n", argv[0]);
		exit(1); }

 char *ct_infile  =   argv[1];
 char *privkey_file = argv[2];
 char *outfile   =    argv[3];


 	OpenSSL_add_all_ciphers();

	FILE * fpriv = fopen(privkey_file,"rb");
	if(!fpriv) {
	    fprintf(stderr, "Failed to open privkey file %s\n", argv[2]);
	    exit(3);}

	EVP_PKEY * privkey = PEM_read_PrivateKey(fpriv, NULL, NULL, NULL);	
		if (!privkey) {
	   	   fprintf(stderr, "Public key load failed\n");
	  	   exit(2);}
 	
 	        fclose(fpriv);


 int ekl = EVP_PKEY_size(privkey);
 int iv_len;
 char cipherName[16];	
 const EVP_CIPHER *cipher;

		FILE * fInput = fopen(ct_infile,"rb");
			if(!fInput) {
			printf("Failed to open file %s.\n",argv[1]);
			exit (2); }

	rewind(fInput);
   	fscanf(fInput, "%s %d %d", cipherName, &ekl, &iv_len);

	//unsigned char * ek =(unsigned char *)malloc(ekl);
	//unsigned char * iv =(unsigned char *)malloc(iv_len);

	unsigned char ek[ekl];
	unsigned char iv[iv_len];
	if (strcmp(cipherName,"AES-256-CBC") == 0)
			cipher = EVP_get_cipherbyname(cipherName);
		if(!cipher) {
		      fprintf(stderr,"Failed in recognizing cipher %s.\n",cipherName);
		      exit(3); }

	if(fread(iv,sizeof(unsigned char) , iv_len, fInput) != iv_len) {
			fprintf(stderr, "Failed to read iv.\n");
			exit(3); }		
		if(fread(ek,sizeof(unsigned char),ekl,fInput) !=ekl){
		 	fprintf(stderr, "Failed to read ek.\n");
			exit(3); }

	EVP_CIPHER_CTX * ctx = EVP_CIPHER_CTX_new();
	if(!(ctx = EVP_CIPHER_CTX_new())){
		fprintf(stderr,"Failed EVP_CIPHER_CTX_new \n");
		      exit(3); }
	if(1 != EVP_OpenInit(ctx, cipher, ek, ekl, iv, privkey)){
		fprintf(stderr,"Failed OpenInit\n");
		      exit(3); }

	FILE * fOutput = fopen(outfile,"wb");
		if(!fOutput){
		fprintf(stderr, "Failed to open input file %s.\n",argv[3]);
		exit(2); }

 unsigned char inputfile_buffer[BUFSIZE+EVP_MAX_BLOCK_LENGTH];
 unsigned char pt[BUFSIZE+EVP_MAX_BLOCK_LENGTH];
 int pt_len;
 int lenght_inputfile = 0;
 int datalen = 0;
 int res;

		while( (res = fread(inputfile_buffer,sizeof(unsigned char),(BUFSIZE),fInput)) > 0 )
		{
			if(!EVP_OpenUpdate(ctx,pt,&pt_len,inputfile_buffer,res)){
			fprintf(stderr, "OpenUpdate is failed.\n");
			exit(3);} else {
				lenght_inputfile += res;
				fwrite(pt,sizeof(unsigned char),pt_len,fOutput);
				datalen += pt_len; }
		}
			if(!EVP_OpenFinal(ctx, pt, &pt_len)) {
 			fprintf(stderr,"OpenFinal is failed.\n");
			exit(2);} else {
				fwrite(pt,sizeof(unsigned char),pt_len,fOutput);			
				datalen += pt_len;} 
				
			
	//printf("the size of input %s: %d bytes.\n", ct_infile, lenght_inputfile );
	//printf("the size of decrypted %s: %d bytes.\n", outfile, datalen );
	
			fclose(fInput);
			fclose (fOutput);

			EVP_CIPHER_CTX_free(ctx);
			//free(ek);
			//free (iv);
	
	
			exit (0);



}


