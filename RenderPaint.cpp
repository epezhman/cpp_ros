#include "RenderPaint.h"
#include "MHDHandler.h"
#include "QMessageBox"
#include <QtWidgets/QLabel> 
#include <QtWidgets/QMainWindow> 
#include <QtWidgets/QPushButton> 
#include <QtWidgets/QGridLayout>
#include <QPainter>
#include <QThread>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>

#include <math.h>
#include "TransferFunction.h"


//modified!


RenderPaint::RenderPaint(QWidget* parent)
: QWidget(parent), m_RawImg(NULL), m_Img(NULL), cbColor(NULL), sbSize(NULL),lePath(NULL),leSavePath(NULL), MyVolume(NULL), m_clickX(0), m_clickY(0),m_realx(0),m_realy(0),m_paint(0), distance(5),n1(0), n2(1), n3(0),iMin(0), iMax(20),theta(0), m_RGBValue(qRgb(0,0,0))
{

	//Eigen::Vector3f low_temp(0,0,0);
	//Eigen::Vector3f up_temp(9,9,9);
	//Eigen::VectorXf dim_temp(3);
	//dim_temp<<10,10,10;
	//ned(low_temp, up_temp, dim_temp);
	m_RawImg = new QImage(180,180,QImage::Format_ARGB32);
	m_Img = new QImage(180, 180, QImage::Format_ARGB32);
	cbColor = new QComboBox(); sbSize = new QSpinBox(); lePath = new QLineEdit(); leSavePath = new QLineEdit();
	
	//MyHandler = new MHDHandler;


	update();
}

void RenderPaint::updateAngle(double value)
{
	theta = value;
	updateParam();
}

void RenderPaint::updateIMin(double value)
{
	iMin = value;
	updateParam();
}

void RenderPaint::updateIMax(double value)
{
	iMax = value;
	updateParam();
}

void RenderPaint::updateDist(double value)
{

	//std::cout << "UpdatePlane(): " << value << std::endl;
	distance = value;
	updateParam();
}

void RenderPaint::updaten1(double value)
{
	//std::cout << "UpdatePlane(): " << value << std::endl;
	n1 = value;
	updateParam();
	
}

void RenderPaint::updaten2(double value)
{
	//std::cout << "UpdatePlane(): " << value << std::endl;
	n2 = value;
	updateParam();
	
}

void RenderPaint::updaten3(double value)
{
	//std::cout << "UpdatePlane(): " << value << std::endl;
	n3 = value;
	updateParam();

	
}

void RenderPaint::RenderLoad()
{
	//QMessageBox::information(this, "QHelloWorld Greeting", QString("Hello Ely!"));
	
	QWidget* LoadPathWindow = new QWidget();
	QLabel* lbPath = new QLabel("Path:");
	lePath->setPlaceholderText("Path to .mhd file");
	QPushButton* pbPath = new QPushButton("Load NOW!!!");
	QGridLayout* glPath = new QGridLayout();
	glPath->addWidget(lbPath, 0, 0);
	glPath->addWidget(lePath, 0, 1);
	glPath->addWidget(pbPath, 1, 0,1,2);
	LoadPathWindow->setLayout(glPath);
	LoadPathWindow->show();
	
	//Call to a window where to insert the image path
	connect(pbPath, SIGNAL(clicked()),
		this, SLOT(LoadImage())
		);

	//std::cout << "vasate load! " << std::endl;		
	
	connect(pbPath, SIGNAL(clicked()),
		LoadPathWindow, SLOT(close())
		);

}

void RenderPaint::updateParam()
{




	//for (int k = 0; k<10; k++)
	//	std::cout << "volume value " << MyVolume->getVoxelLinear(5,5,k) << std::endl;


	theta = theta*3.14/180;
	Eigen::Vector3f rotVol;
	Eigen::MatrixXf rotMat(3,3);
	//rotation along y axis
	rotMat << std::cos(theta), 0, std::sin(theta), 0, 1, 0, -1*std::sin(theta),  0, std::cos(theta);



	float thresh = 0.5;
	//Eigen::Vector3f random_vect ((float)(rand() %1000+1)/1000, (float)(rand() %1000+1)/1000, (float)(rand() %1000+1)/1000);
	Eigen::Vector3f n(n1, n2, n3);
	Eigen::Vector3f n2(0, 0, 1);
	Eigen::Vector3f u,v,next_p;


	u = n.cross(n2);
	v = n.cross(u);
	// normalize u & v
	u.normalize();
	v.normalize();

	Eigen::Vector3f my_point = n*distance;
	//std::cout << "u " << std::endl;
	Eigen::Vector3f volCent = MyVolume->getNumVoxels()/2;
	//std::cout << "volCent" << MyVolume->getNumVoxels()/2 << std::endl;
	//std::cout << "before " << MyVolume->getVoxel(4, 3 , 2) << std::endl;
	// project the volume center to the plane
	Eigen::Vector3f volCent_proj = volCent - n.dot(volCent - my_point)*n;
	Eigen::Vector3f volCent_proj2 = volCent - n2.dot(volCent - n2)*n2;
	//std::cout << "volCent_proj " << volCent_proj << std::endl;

	TransferFunction TF;
	TF.iMin = iMin;
	TF.iMax = iMax;


	// not sure if step should be int?!
	int step = 1;
	//Eigen::Vector3f step(1,1,1);	
	//Eigen::Vector3f intensity(89,89,89);
	float myVal;
	Eigen::Vector2f MIP;
	Eigen::Vector3f planeNorm(0,0,1);
	int planePos(-10);
	int detectPos(30);

	Eigen::AlignedBox3f BoundingBox=MyVolume->getBoundingBox();
	Eigen::Vector3f BBMin=BoundingBox.min();
	Eigen::Vector3f BBMax=BoundingBox.max();
	//Smit's method
	float t0=0;
	float t1=1;
	float tmin, tmax, tymin, tymax,tzmin,tzmax;
	//bool done=0;


	//std::cout << "sin " << sin(90) << std::endl;
	//std::cout << "sin " << sin(45) << std::endl;
	for (int i = -90; i < 90; i++)
	{
		for (int j = -90; j < 90; j++)
		{
		
		//int i = 4;
		//int j = 4;
		//QColor color = TF.classify(MyVolume.getVoxelLinear(((float)i)/10,((float)j)/10,d));
		next_p = volCent_proj + i*u/10 + j*v/10;
		//std::cout << "TF " << TF.classify(10).rgba() << std::endl;
		
		QColor color = TF.classify(MyVolume->getVoxelLinear(next_p[0], next_p[1], next_p[2]));	
		//std::cout << "after my volume "<< std::endl;	
		QRgb rgba = color.rgba();
		//std::cout << "Color of pixel (" << i << ", " << j << ") is: " << color.name().toStdString() << std::endl;
		//std:: cout <<"getVoxelLinear: " << MyVolume->getVoxelLinear(next_p[0], next_p[1], next_p[2]) << std::endl;

		m_Img->setPixel(i+90,j+90, rgba);
		//MIP[i][j] = intensity[i][j].maxCoeff();
		//
		
		// volume rendering
		Eigen::Vector3f startPoint((i+90)/10,(j+90)/10,planePos);
		//std:: cout << "i " << i << "(i+90)/10 " << (i+90)/10 << " j " << j << "(j+90)/10 " << (j+90)/10 << std::endl;
		//std::cout << "start point " << startPoint << std::endl;
		
		Eigen::Vector3f endPoint((i+90)/10,(j+90)/10,detectPos);

		//std::cout << "end point " << endPoint << std::endl;

		Eigen::Vector3f startPoint_rot = rotMat*startPoint;
		Eigen::Vector3f endPoint_rot = rotMat*endPoint;
		Eigen::Vector3f rotRay(endPoint_rot - startPoint_rot);
		//std::cout << "Ray " << endPoint - startPoint << std::endl;
		//std::cout << "Ray rotated " << rotRay << std::endl;
		Eigen::Vector3f rotRay_norm = rotRay;
		rotRay_norm.normalize();
		float maxIntensity(0);
		Eigen::Vector3f delta(0.0001, 0.0001, 0.0001);
		rotRay = rotRay + delta;

		BBMin[0] = floor(BBMin[0]/MyVolume->getSpacing().x());
		BBMin[1] = floor(BBMin[1]/MyVolume->getSpacing().y());
		BBMin[2] = floor(BBMin[2]/MyVolume->getSpacing().z());
		BBMax[0] = floor(BBMax[0]/MyVolume->getSpacing().x());
		BBMax[1] = floor(BBMax[1]/MyVolume->getSpacing().y());
		BBMax[2] = floor(BBMax[2]/MyVolume->getSpacing().z());

		//std::cout<<"rotRay.x()"<<rotRay.x()<<std::endl;
		//std::cout<<"rotRay.y()"<<rotRay.y()<<std::endl;	
		//std::cout<<"rotRay.z()"<<rotRay.z()<<std::endl;
		//std::cout << "BBMin " << BBMin << std::endl;
		//std::cout << "BBMx " << BBMax << std::endl;
		//std::cout << "startpoint " << startPoint_rot << std::endl;
		bool done=0;
		while (done==0)//&&(t1<1))
		{

			if (rotRay[0]>=0) // x Axis
			{
				tmin=(BBMin.x()-startPoint_rot.x())/rotRay.x();
				tmax=(BBMax.x()-startPoint_rot.x())/rotRay.x();
			}
			else
			{
				tmin=(BBMax.x()-startPoint_rot.x())/rotRay.x();
				tmax=(BBMin.x()-startPoint_rot.x())/rotRay.x();
			}
			if (rotRay.y()>=0) // y Axis
			{
				tymin=(BBMin.y()-startPoint_rot.y())/rotRay.y();
				tymax=(BBMax.y()-startPoint_rot.y())/rotRay.y();
			}
			else
			{
				tymin=(BBMax.y()-startPoint_rot.y())/rotRay.y();
				tymax=(BBMin.y()-startPoint_rot.y())/rotRay.y();
			}

		//std::cout << "tmin" << tmin << std::endl;
		
		//std::cout << "tmsx " << tmax << std::endl;

		//std::cout << "tymin" << tymin << std::endl;
		
		//std::cout << "tymsx " << tymax << std::endl;

			if ((tmin>tymax) || (tymin>tmax))
				done=false;
			if (tymin>tmin)
				tmin=tymin;
			if (tymax < tmax)
				tmax = tymax;
			if (rotRay.z()>=0) // z Axis
			{
				tzmin=(BBMin.z()-startPoint_rot.z())/rotRay.z();
				tzmax=(BBMax.z()-startPoint_rot.z())/rotRay.z();
			}
			else
			{
				tzmin=(BBMax.z()-startPoint_rot.z())/rotRay.z();
				tzmax=(BBMin.z()-startPoint_rot.z())/rotRay.z();
			}



		//std::cout << "tzmin" << tzmin << std::endl;
		
		//std::cout << "tzmsx " << tzmax << std::endl;


			if((tmin>tzmax)||(tzmin>tmax))
				{
				done=false;
				break;
				}
			if (tzmin>tmin)
				tmin=tzmin;
			if (tzmax<tmax)
				tmax=tzmax;



			done=((tmin<t1)&&(tmax>t0));
			break;
		}
		
		if (done==1) // then there is an intersection
		{ 

		Eigen::Vector3f entryPoint = startPoint + tmin*rotRay;
		//std:: cout << "current entry " <<entryPoint << std::endl; 


		Eigen::Vector3f exitPoint = startPoint + tmax*rotRay;

		//std:: cout << "i " << i << " j " << j << std::endl;
		//std::cout << "entry " << entryPoint << std::endl; 
		//std::cout << "exit " << exitPoint << std::endl; 

		Eigen::Vector3f stepPoint;

	/*
		
		std::cout << "tmax " << tmax << std::endl;
		std::cout << "exit p " << exitPoint << std::endl;
		std::cout << "entry p " << entryPoint << std::endl;

		double diff1 = exitPoint[0] - entryPoint[0];
		double diff2 = exitPoint[1] - entryPoint[1];
		double diff3 = exitPoint[2] - entryPoint[2];

		std::cout << "diff1 " << diff1 << std::endl;
		std::cout << "diff2 " << diff2 << std::endl;
		std::cout << "diff3 " << diff3 << std::endl;

		double rayLengthdiff1(pow(diff1, 2));
		double rayLengthdiff2(pow(diff2, 2));
		double rayLengthdiff3(pow(diff3, 2));
		std::cout << "rayLengthdiff1 + rayLengthdiff2 + rayLengthdiff3 " << rayLengthdiff1 + rayLengthdiff2 + rayLengthdiff3 << std::endl;
		std::cout << "abs(rayLengthdiff1 + rayLengthdiff2 + rayLengthdiff3) " << abs(rayLengthdiff1 + rayLengthdiff2 + rayLengthdiff3) << std::endl;
		std::cout << "sqrt(abs(rayLengthdiff1 + rayLengthdiff2 + rayLengthdiff3)) " << sqrt(abs(rayLengthdiff1 + rayLengthdiff2 + rayLengthdiff3)) << std::endl; 

		double rayLength = sqrt(abs(rayLengthdiff1 + rayLengthdiff2 + rayLengthdiff3));
		int stepNum = rayLength/step;
		std::cout << "ray length " << rayLength << std::endl;
		//std::cout << "step " << step << std::endl;
	
		//std::cout << "stepNum " << stepNum << std::endl;

*/
		stepPoint = entryPoint;
		while  (stepPoint[0] <  10 &&   stepPoint[1] <  10  && stepPoint[2] <  10 )
		{	
			//stepPoint = entryPoint + k*step*rotRay_norm;
			//std::cout << "step point " << stepPoint << std::endl;
			//if (stepPoint[2] >50)
			//	{
				//std::cout << "i " << i << "j " << j << std::endl;
			//	break;
			//	}
			double myValue = MyVolume->getVoxelLinear(stepPoint[0], stepPoint[1], stepPoint[2]);
			stepPoint = stepPoint + step*rotRay_norm;
			//std::cout << "myvalue " << myValue << std::endl;
			//std::cout << "maxIntensity " << maxIntensity << std::endl;
			if (myValue > maxIntensity)
				maxIntensity = myValue;
			//std::cout << "max val " << maxIntensity << std::endl;
		}

		//maxIntensity = MyVolume->getVoxelLinear(5, 5, 5);
		
		TF.classify(maxIntensity);
		QColor color2 = TF.classify(maxIntensity);
		QRgb rgba2 = color2.rgba();
		m_RawImg->setPixel(i+90,j+90, rgba2);
		//std::cout << "done is 1! " << std::endl;
		}
		
		//std::cout << "done val " << done << std::endl;

				
		//std::cout << "tmin" << tmin << std::endl;
		
		//std::cout << "tmsx " << tmax << std::endl;

		}
	}

	std:: cout << "done! " << std::endl;
	//std::cout << "color! " << TF.classify(intensity).name().toStdString() << std::endl; 
	m_RealSize = m_RawImg->size();
	m_size = m_RawImg->size();

	update();
	

}



void RenderPaint::LoadImage()
{
	QMessageBox::information(
		this,
		"Inside LoadImage",
		QString("Loading ... %1")
		.arg(lePath->text())
		);

	MHDHandler MyHandler;

	// Convert QtString to char*
	std::string name (lePath->text().toStdString().c_str());//;	//" // //"/home/milad/Documents/Neda-c++praktikum/Project/assignment6/build/box.mhd"
	
	//Volume MyVolume = MyHandler->read(name);
	//MyVolume = MyHandler.read(name);
	//d::cout<<ned.getLowerLeft().x();
	MyVolume = new Volume(MyHandler.read(name));
	

	

	//int nvox_x = MyVolume.getNumVoxels()[0];

	//"/home/milad/Documents/Neda-c++praktikum/Project/assignment6/build/box.mhd"

	// 0 index voxel and vector
	//std::cout << "Lower value: " << MyVolume->getVoxel(2,4,4) << std::endl;
	//std::cout << "Linear: " << MyVolume->getVoxelLinear(2.2,4.5,4.8) << std::endl;
	//std::cout << "Upper value: " << MyVolume->getVoxelLinear(3,5,5) << std::endl;

	updateParam();
	

}

void RenderPaint::RenderSave()
{
	QWidget* SavePathWindow = new QWidget();
	QLabel* lbSavePath = new QLabel("SavePath:");
	//QLineEdit* lePath = new QLineEdit();
	leSavePath->setPlaceholderText("C:/MyFiles/imagen...");
	QPushButton* pbSavePath = new QPushButton("Save NOW!!!");
	QGridLayout* glSavePath = new QGridLayout();
	glSavePath->addWidget(lbSavePath, 0, 0);
	glSavePath->addWidget(leSavePath, 0, 1);
	glSavePath->addWidget(pbSavePath, 1, 0, 1, 2);
	SavePathWindow->setLayout(glSavePath);
	SavePathWindow->show();

	//Call to a window where to insert the save path
	connect(pbSavePath, SIGNAL(clicked()),
		this, SLOT(SaveImage())
		);
	connect(pbSavePath, SIGNAL(clicked()),
		SavePathWindow, SLOT(close())
		);

}



void RenderPaint::SaveImage()
{
	m_Img->save(leSavePath->text());
}

void RenderPaint::RenderZoomIn()
{
	m_size = 0.9*m_size; //Reduce the image size in 10%
	*m_Img = m_Img->scaled(m_size, Qt::KeepAspectRatio,Qt::SmoothTransformation);
	update();
}

void RenderPaint::RenderZoomOut()
{
	m_size = 1.1*m_size; //Increase the image size in 10%
	*m_Img = m_Img->scaled(m_size, Qt::KeepAspectRatio,Qt::SmoothTransformation);
	update();
}

void RenderPaint::RenderPenSetUp()
{
	//Open a Box where to choose the color and size
	QWidget* wColorSize = new QWidget;
	//Description
	QLabel* lbInfo = new QLabel("Select Color and Radio of the point (0=single point)", wColorSize);
	lbInfo->setStyleSheet("QLabel { color: black; font-size:12pt; }");

	//Color
	QLabel* lbColor = new QLabel("Color:", wColorSize);
	lbColor->setStyleSheet("QLabel { color: darkRed; font-size:14pt; }");
	cbColor->addItem("Red");
	cbColor->addItem("Green");
	cbColor->addItem("Blue");
	cbColor->addItem("Cyan");
	cbColor->addItem("Magenta");
	cbColor->addItem("Orange");
	cbColor->addItem("Purple");

	//Size
	QLabel* lbSize = new QLabel("Radio:", wColorSize);
	lbSize->setStyleSheet("QLabel { color: darkRed; font-size:14pt; }");
	sbSize->setMinimum(0);
	sbSize->setMaximum(100);
	sbSize->setValue(0);
	
	//PushButtom to start drawing
	QPushButton* pbDraw = new QPushButton("Let's draw!!!");
	pbDraw->setStyleSheet("QPushButton { color: red; font-size:14pt; }");

	//Layout
	QGridLayout* glColor = new QGridLayout();
	glColor->addWidget(lbInfo, 0, 0,1,2);
	glColor->addWidget(lbColor, 1, 0);
	glColor->addWidget(cbColor, 1, 1);
	glColor->addWidget(lbSize, 2, 0);
	glColor->addWidget(sbSize, 2, 1);
	glColor->addWidget(pbDraw, 3, 0,1,2);
	wColorSize->setLayout(glColor);

	wColorSize->show();

	//Connect the PushButton with RenderPenSetUpOn SLOT
	connect(pbDraw, SIGNAL(clicked()),
		this, SLOT(RenderPenSetUpOn())
		);
	connect(pbDraw, SIGNAL(clicked()),
		wColorSize, SLOT(close())
		);
}

void RenderPaint::RenderPenSetUpOff()
{
	m_paint = 0; //Disable Pen, still can reach the RGB values of the pixel x,y without painting
}

void RenderPaint::RenderPenSetUpOn()
{
	m_paint = 1; //Activate Pen
}

void RenderPaint::Drawing()
{
	if (m_paint == 1) //If Pen activated
	{
		//Transform the color's name into qRgb
		if (cbColor->currentText() == "Red")
			m_RGBValue = qRgb(255, 0, 0);
		if (cbColor->currentText() == "Green")
			m_RGBValue = qRgb(0, 255, 0);
		if (cbColor->currentText() == "Blue")
			m_RGBValue = qRgb(0, 0, 255);
		if (cbColor->currentText() == "Cyan")
			m_RGBValue = qRgb(0, 255, 255);
		if (cbColor->currentText() == "Magenta")
			m_RGBValue = qRgb(240, 0, 135);
		if (cbColor->currentText() == "Orange")
			m_RGBValue = qRgb(255, 69, 0);
		if (cbColor->currentText() == "Purple")
			m_RGBValue = qRgb(148, 0, 211);


		//Color the clicked pixel and its neighboors according to radio
		for (int a{ -sbSize->value() }; a <= sbSize->value(); a++)
			{
				for (int b{ -sbSize->value() }; b <= sbSize->value(); b++)
				{
					m_Img->setPixel(m_clickX + a, m_clickY + b, m_RGBValue);

				}

			}

	}
	update();
}

void RenderPaint::SetImage(QImage* image)
{
	//m_size = image->size();
	//m_Img = image;
	//update();
}

void RenderPaint::paintEvent(QPaintEvent* pe)
{
	QPainter p(this);
	//p.scale(0.5, 0.5);
	p.drawImage(QPoint(0,0),*m_Img);
	p.drawImage(QPoint(300,0),*m_RawImg);
}

void RenderPaint::mousePressEvent(QMouseEvent* event)
{

	int x = event->pos().x();
	int y = event->pos().y();
		
	// Calculate scale
	double sx = (double) m_size.width() / (double) m_RealSize.width();
	double sy = (double) m_size.height() / (double) m_RealSize.height();

	QString sx_string = QString::number(sx,'g',2);
	QString sy_string = QString::number(sy, 'g', 2);

	if (x > m_size.width() || y > m_size.height())
	{
		QMessageBox::information(this, "Mouse Event!!!", QString("Out of image size :( "));
		return;
	}

	int x2 = (int)round(double(x)/sx);
	int y2 = (int)round(double(y)/sy);

	QRgb pixel = m_RawImg->pixel(x2, y2);

	QColor color = QColor::fromRgba(pixel);
	
	
	/*QMessageBox::information(this, "Mouse Event!!!",
		QString("x_event= %1, y_event= %2, sx=%3, w=%4, h=%5, x_real=%6, y_real=%7, red=%8, green=%9, blue=%10")
		.arg(x)
		.arg(y)
		.arg(sx_string)
		.arg(m_size.width())
		.arg(m_size.height())
		.arg(x2)
		.arg(y2)
		.arg(color.red())
		.arg(color.green())
		.arg(color.blue()));
*/
	m_clickX = x;
	m_clickY = y;
	m_realx = x2;
	m_realy = y2;

	//When click occurs, emit the signal to Draw if Pen is active and to plot coordinates and RGB components in the uooper left corner
	emit RGBValues(color.red(), color.green(), color.blue(), color.alpha() ,x2, y2);
	connect(this, SIGNAL(RGBValues(int, int, int, int, int, int)),
		this, SLOT(Drawing())
		);
}















