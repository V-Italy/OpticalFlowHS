#define CVX_GRAY50 cvScalar(100)
#define CVX_WHITE  cvScalar(255)
    
int OpticalFlowOpenCV::run
{
    // Initialize, load two images from the file system, and
    // allocate the images and other structures we will need for
    // results.
    
    // exit if no input images
        IplImage *imgA = 0, *imgB = 0;
    imgA = cvLoadImage("OpticalFlow0.jpg",0);
    imgB = cvLoadImage("OpticalFlow1.jpg",0);
    if(!(imgA)||!(imgB)){ printf("One of OpticalFlow0.jpg and/or OpticalFlow1.jpg didn't load\n"); return -1;}
    
    IplImage* velx = cvCreateImage(cvGetSize(imgA),IPL_DEPTH_32F,1);
    IplImage* vely = cvCreateImage(cvGetSize(imgA),IPL_DEPTH_32F,1);
    
    IplImage* imgC = cvCreateImage(cvGetSize(imgA),IPL_DEPTH_8U,3);
    
    cvNamedWindow( "OpticalFlow0" );
    cvNamedWindow( "OpticalFlow1" );
    cvNamedWindow( "Flow Results" );
    
    cvShowImage( "OpticalFlow0",imgA );
    cvShowImage( "OpticalFlow1",imgB );
    
    // Call the actual Horn and Schunck algorithm
    //
    cvCalcOpticalFlowHS( 
        imgA, 
        imgB, 
        0,
        velx,
        vely,
        .10,
        cvTermCriteria( 
            CV_TERMCRIT_ITER | CV_TERMCRIT_EPS,
            imgA->width,
            1e-6
        )
    );
    
    // Now make some image of what we are looking at:
    //
    cvZero( imgC );
    int step = 4;
    for( int y=0; y<imgC->height; y += step ) {
        float* px = (float*) ( velx->imageData + y * velx->widthStep );
        float* py = (float*) ( vely->imageData + y * vely->widthStep );
        for( int x=0; x<imgC->width; x += step ) {
            if( px[x]>1 && py[x]>1 ) {
                cvCircle(
                    imgC,
                    cvPoint( x, y ),
                    2,
                    CVX_GRAY50,
                    -1
                );
                cvLine(
                    imgC,
                    cvPoint( x, y ),
                    cvPoint( x+px[x]/2, y+py[x]/2 ),
                    CV_RGB(255,0,0),
                    1,
                    0
                );
            }
        }
    }
    // show tracking
    cvShowImage( "Flow Results",imgC );
        
    cvWaitKey(0);
    
    // destroy windows
    cvDestroyWindow( "OpticalFlow0" );
    cvDestroyWindow( "OpticalFlow1" );
    cvDestroyWindow( "Flow Results" );
    // release memory
    cvReleaseImage( &imgA );
    cvReleaseImage( &imgB );
    cvReleaseImage( &imgC );
    
    return 0;
}  