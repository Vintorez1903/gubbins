#include <stdlib.h>

const char base64String[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const char paddingChar='=';

char intToB64Char(int in){
	//this string is a URL safe character set for encoding. the padding character is \')\'
	return base64String[in];
}

//padding function
int getRequiredPadding(int in){
	if(in%3==0){
		return 0;
	}
	
	return (3-in%3);
}

int getPaddedSize(int in){
	if(in%3==0){
		return 4*(in/3);
	}
	
	return 4*((in+(3-in%3))/3);
}

int strPtrSize(char in[]){
	int inputSize = 0;
	//get size of input string
    while(in[inputSize])
    {
		inputSize++;
	}
	
	return inputSize;
}

//
int B64EncodeBlock(char workingSegment[], char *output, int encodedIndex){
	unsigned int combined = (workingSegment[0] << 16) + (workingSegment[1] << 8) + workingSegment[2];   //pass unencoded data into int via bit shift
	for(int i = 18; i >= 0; i-=6){																		
		output[encodedIndex] = combined>>i&0x3F;						//pass back out into output array
		output[encodedIndex] = intToB64Char(output[encodedIndex]);		//convert int into ASCII char
		encodedIndex++;
	}

	return encodedIndex;
}

//DO NOT USE WITH ANY ARRAY OTHER THAN THE WORKING ARRAY
void purgeWorkingArray(char workingSegment[]){
	int size = 3*sizeof(char);
	
	for(int i = 0; i < size; i++){
				workingSegment[i]=0;
			}
}

void padAndTerminate (char string[], int inputSize, int encodedSize){
	int requiredPadding = getRequiredPadding(inputSize);
	for(int i = encodedSize-1; i > encodedSize-1-requiredPadding; i--){		//replace the last few empty characters with the padding characters, if applicable
		string[i]=paddingChar;
	}
	string[encodedSize]=0;													//append null terminator to output string
}

char *b64Encode(char in[]){
	int inputSize = strPtrSize(in);
	int index = 0;
	int workingIndex = 0;
	int encodedIndex = 0;
	char workingSegment[3];
	int encodedSize = getPaddedSize(inputSize);
	
	char *output = (char *)malloc(encodedSize+1);
	
	for(int i = 0; i < encodedSize; i++){
		
		if(in[index]){
			workingSegment[workingIndex]=in[index];
		}
		if(workingIndex>=2){
			workingIndex=0;
			encodedIndex=B64EncodeBlock(workingSegment,output,encodedIndex);
			
			purgeWorkingArray(workingSegment);
		}
		
		else{
			workingIndex++;
		}
		
		index++;
    }
	
	padAndTerminate(output,inputSize,encodedSize);
	
	return output;
}
