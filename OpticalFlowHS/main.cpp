#include "HSOpticalFlowOpenCL.hpp"
#include "OpticalFlowOpenCV.hpp"

int	main(int argc, char * argv[])
{
	std::cout<<"OpenCL kamera!\n";
	HSOpticalFlowOpenCL clOpticalFlow("OpticalFlow", "-cam", 15, 3, 1, "CPU");
	clOpticalFlow.initialize();
	clOpticalFlow.setup();
	clOpticalFlow.run();
	clOpticalFlow.cleanup();
	return 0;

	/*if (argc == 1){
		std::cout<<"Nie zostaly podane zadne parametry do funkcji main.\nKoncze dzialanie!\n";
		return 0;
	}*/
	if (strcmp(argv[1], "-o") == 0){
		if (strcmp(argv[2], "-hd") == 0){
			if (argc != 10){
				std::cout<<"Bledna lista argumentow!\n";
				return 0;
			}
			else
			{
				char *src = argv[2];
				char *input1 = argv[3];
				char *input2 = argv[4];
				char *output = argv[5];
				int alpha = atoi(argv[6]);
				int it = atoi(argv[7]);
				int gs = atoi(argv[8]);
				char* dType = argv[9];

				std::cout<<"OpenCL dysk!\n";

				HSOpticalFlowOpenCL clOpticalFlow("OpticalFlow", src, input1, input2, output, alpha, it, gs, dType);
				clOpticalFlow.initialize();
				clOpticalFlow.setup();
				clOpticalFlow.run();
				clOpticalFlow.cleanup();
			}
		}
		else if (strcmp(argv[2], "-cam") == 0){
			if (argc != 7){
				std::cout<<"Bledna lista argumentow!\n";
				return 0;
			}
			else
			{
				char *src = argv[2];
				int alpha = atoi(argv[3]);
				int it = atoi(argv[4]);
				int gs = atoi(argv[5]);
				char* dType = argv[6];

				std::cout<<"OpenCL kamera!\n";
				HSOpticalFlowOpenCL clOpticalFlow("OpticalFlow", src, alpha, it, gs, dType);
				clOpticalFlow.initialize();
				clOpticalFlow.setup();
				clOpticalFlow.run();
				clOpticalFlow.cleanup();
			}
		}
	}
	//else if (strcmp(argv[1], "-ref") == 0)
	else
	{
		std::cout<<"OpenCV kamera!\n";
		OpticalFlowOpenCV *e = new OpticalFlowOpenCV();
		e->run();
	}
	getchar();
	return 0;
}