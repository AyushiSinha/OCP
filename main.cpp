#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "Image/image.h"
#include "Util/cmdLineParser.h"

void ShowUsage(char* ex){
	printf("Usage %s:\n",ex);
	printf("\t--in <input image> --out <output image>\n");
	//printf("\t[--noisify			   <size of noise>]\n");
	//printf("\t[--brighten              <brightening factor>]\n");
	//printf("\t[--gray]\n");
	//printf("\t[--contrast              <contrast factor>]\n");
	//printf("\t[--saturate              <saturation factor>]\n");
	//printf("\t[--quantize       <bits per channel>]\n");
	//printf("\t[--rDither        <bits per channel with random dithering>]\n");
	//printf("\t[--oDither2x2     <bits per channel with ordered dithering>]\n");
	//printf("\t[--fsDither       <bits per channel with Floyd-Steinberg dithering>]\n");
	//printf("\t[--composite      <overlay image> <matte image>\n");
	//printf("\t[--bnMorph        <destination image> <line segment pair list> <time step>\n");
	//printf("\t[--crop                  <x1> <y1> <x2> <y2>]\n");
	//printf("\t[--scaleNearest   <scale factor>\n");
	//printf("\t[--scaleBilinear  <scale factor>\n");
	//printf("\t[--scaleGaussian  <scale factor>\n");
	//printf("\t[--rotateNearest  <angle>\n");
	//printf("\t[--rotateBilinear <angle>\n");
	//printf("\t[--rotateGaussian <angle>\n");
	//printf("\t[--blur3x3]\n");
	//printf("\t[--edges3x3]\n");
	//printf("\t[--fun]\n");
	//printf("\t[--combine               <image2>]\n");
	//printf("\t[--annotations           <image2>]\n");
	//printf("\t[--bilateral             <spatial sigma> <range sigma>]\n");
	//printf("\t[--average               <image2>]\n");
	//printf("\t[--add                   <image2>]\n");
	printf("\t[--axoplasmicreticula]\n"); 
	/*printf("\t[--subtract              <image2>]\n");
	printf("\t[--trackAPR              <image_before> <image_after>]\n");
	printf("\t[--track]                <annotation ID>]\n");
	printf("\t[--compare]              <image2>]\n");
	printf("\t[--vesicles]\n");
	printf("\t[--butons]\n");*/
}
//int ReadImage(char* fileName,Image32& img){
//	char* ext=GetFileExtension(fileName);
//	int ret=0;
//	if(!strcasecmp(ext,"bmp")){ret=BMPReadImage(fileName,img);}
//	else if(!strcasecmp(ext,"jpg") || !strcasecmp(ext,"jpeg")){ret=JPEGReadImage(fileName,img);}
//	else {};	// Unknown format
//	delete[] ext;
//	return ret;
//}
//int WriteImage(char* fileName,Image32& img){
//	char* ext=GetFileExtension(fileName);
//	int ret=0;
//	if(!(img.width()*img.height())){
//		delete[] ext;
//		return 0;
//	}
//	if(!strcasecmp(ext,"bmp")){ret=BMPWriteImage(img,fileName);}
//	else if(!strcasecmp(ext,"jpg") || !strcasecmp(ext,"jpeg")){ret=JPEGWriteImage(img,fileName);}
//	else {};	// Unknown format
//	delete[] ext;
//	return ret;
//}

//int main(int argc,char* argv[]){
void mexFunction( int nlhs , mxArray *plhs[] , int argc , const mxArray *prhs[] ) {

	if (argc == 0)
	{
		ShowUsage("FindReticula") ;
		return ;
	}
	
	char** argv = new char*[argc] ;
	for ( int i = 0 ; i < argc ; i++ )
	{
		char* arg = (char *)mxArrayToString(prhs[i]) ;
		argv[i] = strdup(arg) ;
		mxFree(arg);
	}
	
	//Image32 inImage,outImage;
	cmdLineString In , Out ;
	//cmdLineFloat RandomNoise , Brightness , Contrast , Saturation , ScaleNearest , ScaleBilinear , ScaleGaussian , RotateNearest , RotateBilinear , RotateGaussian ;
	//cmdLineInt Quantize , RDither , ODither2X2 , FSDither ;
	//cmdLineStringArray Composite(2) , BNMorph(3) , Combine(1) , Average(1) , Add(1) , Annotations(1) , TrackAPR(2) , Compare(1), Butons(1) ;
	//cmdLineIntArray Crop(4) , Track(1) ;
	//cmdLineFloatArray Bilateral(2) ;
	cmdLineReadable /*Gray , Blur3X3 , Edges3X3 , Fun , Subtract ,*/ APR /*, Vesicles*/ ;
	
	char* paramNames[]={
		"in","out",
		//"noisify","brighten","gray","contrast","saturate",
		//"quantize","rDither","oDither2x2","fsDither",
		//"blur3x3","edges3x3",
		//"composite",
		//"scaleNearest","scaleBilinear","scaleGaussian",
		//"rotateNearest","rotateBilinear","rotateGaussian",
		//"fun","crop",
		//"bnMorph",
		//"combine",
		//"bilateral",
		//"average",
		//"add",
		"axoplasmicreticula"/*,
		"subtract",
		"trackAPR",
		"annotations",
		"track",
		"compare",
		"vesicles",
		"butons"*/
	};

	cmdLineReadable* params[]=
	{
		&In,&Out,
		//&RandomNoise,&Brightness,&Gray,&Contrast,&Saturation,
		//&Quantize,&RDither,&ODither2X2,&FSDither,
		//&Blur3X3,&Edges3X3,
		//&Composite,
		//&ScaleNearest,&ScaleBilinear,&ScaleGaussian,
		//&RotateNearest,&RotateBilinear,&RotateGaussian,
		//&Fun,&Crop,
		//&BNMorph,
		//&Combine,
		//&Bilateral,
		//&Average,
		//&Add,
		&APR/*,
		&Subtract,
		&TrackAPR,
		&Annotations,
		&Track,
		&Compare,
		&Vesicles,
		&Butons*/
	};

	//cmdLineParse(argc-1,&argv[1],paramNames,sizeof(paramNames)/sizeof(char*),params); // <-- CPP
	cmdLineParse(argc,&argv[0],paramNames,sizeof(paramNames)/sizeof(char*),params); // <-- MATLAB

	// Check that the input and output files have been set
	if(!In.set || !Out.set){
		if(!In.set)	{printf("Input image was not set\n");}
		else		{printf("Output image was not set\n");}
		//ShowUsage(argv[0]);
		ShowUsage("FindReticula") ;
		return ; //EXIT_FAILURE;
	}

	// Try to read in the input image
	//if(!ReadImage(In.value,inImage)){
	//	printf("Could not read image: %s\n",In.value);
	//	return ; //EXIT_FAILURE;
	//}
	//printf("Input dimensions: %dx%d\n",inImage.width(),inImage.height());
	
	/*if (Compare.set) {
		Image32 im;
		if ( !ReadImage(Compare.value[0], im) )
			printf( "Could not read image for comparing: %s\n", Compare.value[0]);
		else if ( !inImage.Compare(im , outImage) )
			printf( "Could not compare images\n" );
	}

	if (Average.set) {
		Image32 im;
		if(!ReadImage(Average.value[0],im)){
			printf("Could not read image for averaging: %s\n",Average.value[0]);
		}
		
		else if(!inImage.Average(im,outImage)){
			printf("Could not average images\n");
		}
	}

	if (Add.set) {
		Image32 im;
		if(!ReadImage(Add.value[0],im)){
			printf("Could not read image for adding: %s\n",Add.value[0]);
		}
		
		else if(!inImage.Add(im,outImage)){
			printf("Could not add images\n");
		}
	}

	if(Bilateral.set) {
		if ( !inImage.BilateralFiltering(Bilateral.value[0], Bilateral.value[1], outImage) )
			printf("Could not apply bilateral filter\n");
	}

	if (Combine.set) {
		Image32 im;
		if(!ReadImage(Combine.value[0],im)){
			printf("Could not read image for combining: %s\n",Combine.value[0]);
		}
		else if(!inImage.Combine(im,outImage)){
			printf("Could not combine images\n");
		}
	}*/
	if(APR.set){

		MatlabImage image(prhs[1]) ;
		MatlabImage out(prhs[3]) ;

		//string z, z1, z2, z3, z4;
		//z1 = In.value[11]; z2 = In.value[12]; z3 = In.value[13]; z4 = In.value[14];
		//z = z1+z2+z3+z4;
		//if(!inImage.AxoPlasmicReticula(outImage)){
		if (!image.AxoplasmicReticula(image , out)) {
			printf("Could not compute axoplasmic reticula in the image\n");
		}
		return ;
	}

	//if (Vesicles.set) {
	//	string z = "";
	//	if ( !inImage.Vesicles( outImage , z ) ) {
	//		printf("Count not compute vesicles in the image\n");
	//	}
	//}

	//if (Butons.set) {
	//	string z = "" ;
	//	Image32 im ;
	//	if ( !ReadImage( Butons.value[0] , im ) ) {
	//		printf("Count not read vesicle region image: %s\n" , Butons.value[0]);
	//	}
	//	else if ( !inImage.Butons( im , outImage , z ) ) {
	//		printf("Cound not compute butons in the image\n");
	//	}
	//}
	//	

	//if (TrackAPR.set){
	//	Image32 before, after;
	//	string z, z1, z2, z3, z4;
	//	z1 = In.value[21]; z2 = In.value[22]; z3 = In.value[23]; z4 = In.value[24];
	//	z = z1+z2+z3+z4;
	//	if ( !ReadImage(TrackAPR.value[0], before) )
	//		printf("Could not read the image before %s: %s\n", In.value[0], TrackAPR.value[0]);
	//	else if (!ReadImage(TrackAPR.value[1], after) )
	//		printf("Could not read the image after %s: %s\n", In.value[0], TrackAPR.value[1]);
	//	else if ( !inImage.TrackAPR(before, inImage, outImage, z , after) )
	//		printf("Could not track axoplasmic reticula in z\n");
	//}

	//if (Annotations.set){
	//	Image32 im;
	//	if ( !ReadImage(Annotations.value[0], im) )
	//		printf("Could not read the image to combine annotations with %s: %s\n", In.value[0], Annotations.value[0]);
	//	else if ( !inImage.Annotations(im, outImage) )
	//		printf("Could not combine annotations\n");

	//}

	//if (Track.set) {
	//	string z, z1, z2, z3, z4;
	//	z1 = In.value[0]; z2 = In.value[1]; z3 = In.value[2]; z4 = In.value[3];
	//	z = z1+z2+z3+z4;
	//	if ( !inImage.Track( outImage , z , Track.value[0] ) )
	//		printf("Could not track axoplasmic reticula...\n");
	//}

	//if (Subtract.set){
	//	if ( !inImage.Subtract(outImage) ) {
	//		printf("Could not subtract images\n");
	//	}
	//}
	//// Filter the image
	//if(RandomNoise.set){
	//	if(!inImage.AddRandomNoise(RandomNoise.value,outImage)){
	//		printf("Could not add noise to the image\n");
	//	}
	//}
	//if(Brightness.set){
	//	if(!inImage.Brighten(Brightness.value,outImage)){
	//		printf("Could not change the brightness of the image\n");
	//	}
	//}
	//if(Gray.set){
	//	if(!inImage.Luminance(outImage)){
	//		printf("Could not compute a luminance image\n");
	//	}
	//}
	//if(Contrast.set){
	//	if(!inImage.Contrast(Contrast.value,outImage)){
	//		printf("Could not change the contrast of the image\n");
	//	}
	//}
	//if(Saturation.set){
	//	if(!inImage.Saturate(Saturation.value,outImage)){
	//		printf("Could not change saturation of the image\n");
	//	}
	//}
	//if(Quantize.set){
	//	if(!inImage.Quantize(Quantize.value,outImage)){
	//		printf("Could not change the number of bits per channel (quanitzation)\n");
	//	}
	//}

	//if(RDither.set){
	//	if(!inImage.RandomDither(RDither.value,outImage)){
	//		printf("Could not change the number of bits per channel (random dither)\n");
	//	}
	//}
	//if(Composite.set){
	//	Image32 overlay,matte;
	//	// Read in the target image
	//	if(!ReadImage(Composite.value[0],overlay)){
	//		printf("Could not read overlay image for compositing: %s\n",Composite.value[0]);
	//	}
	//	// Read in the matte image
	//	else  if(!ReadImage(Composite.value[1],matte)){
	//		printf("Could not read matte image for compositing: %s\n",Composite.value[1]);
	//	}
	//	// Set the alpha value of the overlay image using the values of the matte image
	//	else if(!overlay.SetAlpha(matte)){
	//		printf("could not use matte to set the alpha value\n");
	//	}
	//	// Perform the compositing
	//	else if(!inImage.Composite(overlay,outImage)){
	//		printf("Could not composite images\n");
	//	}
	//}
	//if(Blur3X3.set){
	//	if(!inImage.Blur3X3(outImage)){
	//		printf("Could not blur the image\n");
	//	}
	//}
	//if(Edges3X3.set){
	//	if(!inImage.EdgeDetect3X3(outImage)){
	//		printf("Could not detect the edges of the image\n");
	//	}
	//}
	//if(ODither2X2.set){
	//	if(!inImage.OrderedDither2X2(ODither2X2.value,outImage)){
	//		printf("Could not change the number of bits per channel (ordered dither)\n");
	//	}
	//}
	//if(FSDither.set){
	//	if(!inImage.FloydSteinbergDither(FSDither.value,outImage)){
	//		printf("Could not change the number of bits per channel (Floyd-Steinberg dither)\n");
	//	}
	//}
	//if(ScaleNearest.set){
	//	if(!inImage.ScaleNearest(ScaleNearest.value,outImage)){
	//		printf("Could not scale the image\n");
	//	}
	//}
	//if(ScaleBilinear.set){
	//	if(!inImage.ScaleBilinear(ScaleBilinear.value,outImage)){
	//		printf("Could not scale the image\n");
	//	}
	//}
	//if(ScaleGaussian.set){
	//	if(!inImage.ScaleGaussian(ScaleGaussian.value,outImage)){
	//		printf("Could not scale the image\n");
	//	}
	//}
	//if(RotateNearest.set){
	//	if(!inImage.RotateNearest(RotateNearest.value,outImage)){
	//		printf("Could not rotate the image\n");
	//	}
	//}
	//if(RotateBilinear.set){
	//	if(!inImage.RotateBilinear(RotateBilinear.value,outImage)){
	//		printf("Could not rotate the image\n");
	//	}
	//}
	//if(RotateGaussian.set){
	//	if(!inImage.RotateGaussian(RotateGaussian.value,outImage)){
	//		printf("Could not rotate the image\n");
	//	}
	//}

	//if(Fun.set){
	//	if(!inImage.FunFilter(outImage)){
	//		printf("Could not apply a fun filter to the image\n");
	//	}
	//}
	//if(Crop.set){
	//	if(!inImage.Crop(Crop.value[0],Crop.value[1],Crop.value[2],Crop.value[3],outImage)){
	//		printf("Could not crop the image\n");
	//	}
	//}

	//if(BNMorph.set){
	//	float timeStep=(float)atof(BNMorph.value[2]);
	//	Image32 dest;
	//	OrientedLineSegmentPairs olsp;

	//	// Read the destination image
	//	if(!ReadImage(BNMorph.value[0],dest)){
	//		printf("Could not read destination image for morph: %s\n",BNMorph.value[0]);
	//	}
	//	// Read in the list of corresponding line segments
	//	else if(!olsp.read(BNMorph.value[1])){
	//		printf("Could not read in oriented line segment pairs from: %s\n",BNMorph.value[1]);
	//	}
	//	// Perform the morph
	//	else if(!Image32::BeierNeelyMorph(inImage,dest,olsp,timeStep,outImage)){
	//		printf("Could not morph images\n");
	//	}
	//}


	//printf("Output dimensions: %dx%d\n",outImage.width(),outImage.height());
	// Try to write out the output image
	//if(!WriteImage(Out.value,outImage)){
	//	printf("Could not write image: %s\n",Out.value);
	//	return ; //EXIT_FAILURE;
	//}
	return ; //EXIT_SUCCESS;
}
