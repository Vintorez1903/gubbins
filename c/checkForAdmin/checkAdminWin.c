int checkIfAdmin(){
	char buffer[14];
	
	FILE *fp;
	fp = popen("net session 2>&1", "r");
	if (fp == NULL) {
        perror("popen failed");
        return 1;
    }
	
	fgets(buffer, sizeof(buffer), fp);
	//printf("%s", buffer);
	
	int status = pclose(fp);
	
	if(status==-1){
		perror("could not close reader");
		return -1;
	}
	int notAdmin = strcmp("System error 5",buffer);
	
	if(notAdmin==1){
		return 0;
	}
	
	else{
		return 1;
	}
	
	return 0;	
}
