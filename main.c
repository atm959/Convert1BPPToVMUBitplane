#include <stdio.h>

#include "stb_image.c"

int main(int argc, char** argv){
	unsigned char* imageData;
	int width = 0, height = 0, nChannels = 0;

	imageData = stbi_load("image.png", &width, &height, &nChannels, STBI_grey);

	if(imageData){
		printf("Image loaded successfully.\n\n");
	} else {
		printf("Failed to load the image!\n");
		return -1;
	}

	if((width != 48) || (height != 32)){
		printf("The image is not 48x32!\n");
		return -1;
	}

	if(nChannels > 1){
		printf("The image isn't 8-bit grayscale!\n");
		return -1;
	}

	printf("Width: %d\n", width);
	printf("Height: %d\n", height);
	printf("Number of Channels: %d\n", nChannels);

	int numBytes = (width * height) / 8;
	printf("Number of output bytes: %d\n", numBytes);

	unsigned char* output = malloc(numBytes);

	int tempCounter = 0;
	int tempCounter2 = 0;
	int tempCounter3 = 0;

	FILE* outputFile = fopen("output.txt", "w");

	fprintf(outputFile, "unsigned char vmuImage[%d] = {\n\t0b", numBytes);

	for(int i = (numBytes - 1); i >= 0; i--){
		for(int j = 7; j >= 0; j--){
			int offset = (i * 8) + j;
			unsigned char isWhite = imageData[offset] / 255;
			unsigned char isBlack = !isWhite;
			fprintf(outputFile, "%d", isBlack);

			tempCounter++;
			if(tempCounter > 7){
				if(tempCounter2 < (numBytes - 1)){
					tempCounter = 0;
					tempCounter3++;
					if(tempCounter3 < 6){
						fprintf(outputFile, ", 0b");
					} else {
						fprintf(outputFile, ",\n\t0b");
						tempCounter3 = 0;
					}
				}
			}
		}
		tempCounter2++;
	}

	fprintf(outputFile, "\n};");

	fclose(outputFile);

	free(imageData);
	free(output);

	return 0;
}