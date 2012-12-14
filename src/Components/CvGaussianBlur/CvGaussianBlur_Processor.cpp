/*!
 * \file CvGaussianBlur_Processor.cpp
 * \brief
 * \author mstefanc
 * \date 2010-07-05
 */

#include <memory>
#include <string>

#include "CvGaussianBlur_Processor.hpp"
#include "Logger.hpp"

namespace Processors {
namespace CvGaussianBlur {

CvGaussianBlur_Processor::CvGaussianBlur_Processor(const std::string & name) : Base::Component(name),
		sigmax("sigmax", 0.0, "range"),
		sigmay("sigmay", 0.0, "range"),
		kernel_width("kernel_width", 3, "range"),
		kernel_height("kernel_height", 3, "range")
{
	sigmax.setToolTip("Gaussian kernel standard deviation in X direction");
	sigmax.addConstraint("0.0");
	sigmax.addConstraint("10.0");
	sigmay.setToolTip("Gaussian kernel standard deviation in Y direction");
	sigmay.addConstraint("0.0");
	sigmay.addConstraint("10.0");

	kernel_width.addConstraint("0");
	kernel_width.addConstraint("10");
	kernel_height.addConstraint("0");
	kernel_height.addConstraint("10");

	LOG(LTRACE) << "Hello CvGaussianBlur_Processor\n";
}

CvGaussianBlur_Processor::~CvGaussianBlur_Processor()
{
	LOG(LTRACE) << "Good bye CvGaussianBlur_Processor\n";
}

void CvGaussianBlur_Processor::prepareInterface() {
	CLOG(LTRACE) << "CvGaussianBlur_Processor::prepareInterface\n";

	h_onNewImage.setup(this, &CvGaussianBlur_Processor::onNewImage);
	registerHandler("onNewImage", &h_onNewImage);

	registerStream("in_img", &in_img);

	registerStream("out_img", &out_img);

	addDependency("onNewImage", &in_img);
}



bool CvGaussianBlur_Processor::onInit()
{
	LOG(LTRACE) << "CvGaussianBlur_Processor::initialize\n";

	return true;
}

bool CvGaussianBlur_Processor::onFinish()
{
	LOG(LTRACE) << "CvGaussianBlur_Processor::finish\n";

	return true;
}

bool CvGaussianBlur_Processor::onStep()
{
	LOG(LTRACE) << "CvGaussianBlur_Processor::step\n";
	return true;
}

bool CvGaussianBlur_Processor::onStop()
{
	return true;
}

bool CvGaussianBlur_Processor::onStart()
{
	return true;
}

void CvGaussianBlur_Processor::onNewImage()
{
	LOG(LTRACE) << "CvGaussianBlur_Processor::onNewImage\n";
	try {
		cv::Mat img = in_img.read();
		//cv::Mat out = img.clone();
		cv::GaussianBlur(img, img, cv::Size(kernel_width, kernel_height), sigmax, sigmay);
		out_img.write(img);
		newImage->raise();
	} catch (...) {
		LOG(LERROR) << "CvGaussianBlur_Processor::onNewImage failed\n";
	}
}

}//: namespace CvGaussianBlur
}//: namespace Processors
