#include "window.h"
#include "RenderPaint.h"
#include "QMessageBox"
#include <QImage>
#include <QtWidgets/QPushButton> 

window::window(QWidget* parent)
: QWidget(parent), m_Load(NULL), m_Save(NULL), m_ZoomIn(NULL), m_ZoomOut(NULL), m_PenSetUp(NULL), m_PenSetUpOff(NULL), m_I(NULL), m_lblI(NULL), m_GridLayout(NULL), m_lblRGB(NULL), slider(NULL)
{
	setupWindow();
}

void window::setupWindow()
{
	//create left side buttons
	m_Load = new QPushButton;
	m_Load->setText("Load");
	m_Save = new QPushButton;
	m_Save->setText("Save");
	m_ZoomIn = new QPushButton;
	m_ZoomIn->setText("ZoomIn");
	m_ZoomOut = new QPushButton;
	m_ZoomOut->setText("ZoomOut");
	m_PenSetUp = new QPushButton;
	m_PenSetUp->setText("PenSetUpOn");
	m_PenSetUpOff = new QPushButton;
	m_PenSetUpOff->setText("PenSetUpOff");
	m_lblRGB = new QLabel;
	m_I = new QPixmap;
	m_lblI = new QLabel;
	m_lblI->setPixmap(*m_I);

	slider = new QSlider;
	sliderLabel = new QLabel;
	sliderLabel->setText("distance");
        slider->setOrientation(Qt::Horizontal);
    	slider->setMinimum(0);
    	slider->setMaximum(20);
    	slider->setValue(5);

	spinBox = new QDoubleSpinBox;
	spinBox->setRange(0, 20);
	spinBox->setValue(5);
	spinBox->setSingleStep(1);

	nLabel = new QLabel;
	nLabel->setText("normal");

	n1 = new QSlider;
        n1->setOrientation(Qt::Horizontal);
    	n1->setMinimum(0);
    	n1->setMaximum(1);
    	n1->setValue(0);
	spin1 = new QDoubleSpinBox;
	spin1->setRange(0, 1);
	spin1->setValue(0);
	spin1->setSingleStep(0.01);

	n2 = new QSlider;
        n2->setOrientation(Qt::Horizontal);
    	n2->setMinimum(0);
    	n2->setMaximum(1);
    	n2->setValue(1);
	spin2 = new QDoubleSpinBox;
	spin2->setRange(0, 1);
	spin2->setValue(1);
	spin2->setSingleStep(0.01);


	n3 = new QSlider;
        n3->setOrientation(Qt::Horizontal);
    	n3->setMinimum(0);
    	n3->setMaximum(1);
    	n3->setValue(0);
	spin3 = new QDoubleSpinBox;
	spin3->setRange(0, 1);
	spin3->setValue(0);
	spin3->setSingleStep(0.01);

	mprLayout = new QHBoxLayout;
	mpr = new QGroupBox;
    	mprLayout->addWidget(n1, 0 , 0 );
    	mprLayout->addWidget(n2, 1 , 0 );
    	mprLayout->addWidget(n3, 2 , 0 );
    	mpr->setTitle("Normal");
    	mpr->setLayout(mprLayout);

	IntensityRange = new QLabel;
	IntensityRange->setText("Classification Intensity Range");

	//IntensityRangeGroup()
	//{
	spinIntensityMin = new QDoubleSpinBox;
	spinIntensityMin->setRange(0,255);
	spinIntensityMin->setValue(0);
	spinIntensityMin->setSingleStep(1);

	spinIntensityMax = new QDoubleSpinBox;
	spinIntensityMax->setRange(0,255);
	spinIntensityMax->setValue(255);
	spinIntensityMax->setSingleStep(1);
	//}

	rotLabel = new QLabel;
	rotLabel->setText("rotation around Y");

	rotSpin = new QDoubleSpinBox;
	rotSpin->setRange(0,360);
	rotSpin->setValue(0);
	rotSpin->setSingleStep(1);
	

	//create a grid layout and assign the widgets to the grid locations
	m_GridLayout = new QGridLayout;
	m_GridLayout->addWidget(m_Load, 0, 0, 1, 2);
	m_GridLayout->addWidget(m_Save, 1, 0, 1, 2);
	m_GridLayout->addWidget(m_ZoomIn, 2, 0);
	m_GridLayout->addWidget(m_ZoomOut, 2, 1);	
	m_GridLayout->addWidget(m_PenSetUp, 3, 0);
	m_GridLayout->addWidget(m_PenSetUpOff, 3, 1);
	m_GridLayout->addWidget(m_lblRGB, 0, 3);

	m_GridLayout->addWidget(IntensityRange);
	m_GridLayout->addWidget(spinIntensityMin);
	m_GridLayout->addWidget(spinIntensityMax);

	m_GridLayout->addWidget(sliderLabel, 7, 0, 1,2);
	m_GridLayout->addWidget(spinBox, 7, 1, 1, 2);	
	m_GridLayout->addWidget(slider, 8, 0, 1, 2);	
	//m_GridLayout->addWidget(nLabel, 6, 0, 1, 2);	
	//m_GridLayout->addWidget(n1, 9, 0, 1, 2);	
	m_GridLayout->addWidget(spin1, 9, 0, 1, 2);
	//m_GridLayout->addWidget(n2, 10, 0, 1, 2);
	m_GridLayout->addWidget(spin2, 10, 0, 1, 2);	
	//m_GridLayout->addWidget(n3,11, 0, 1, 2);
	m_GridLayout->addWidget(spin3, 11, 0, 1, 2);	
	m_GridLayout->addWidget(rotLabel,12,0,1,2);
	m_GridLayout->addWidget(rotSpin, 12, 1, 1, 2);

	setLayout(m_GridLayout);

	/*connect(m_Load, SIGNAL(clicked()),
		this, SLOT(LoadClicked())
		);*/
	/*QImage* image = new QImage;
	image->load("C:/Users/eLYpC/Documents/C++Praktikum/Part1/assignment6/GenesInSpace.png");
	*/

	//Load Clicked
	RenderPaint* otro = new RenderPaint(NULL);
	connect(m_Load, SIGNAL(clicked()),
		otro, SLOT(RenderLoad())
		);
	m_GridLayout->addWidget(otro, 0, 4, 3, 6);
	setLayout(m_GridLayout);

	//Save Clicked
	connect(m_Save, SIGNAL(clicked()),
		otro, SLOT(RenderSave())
		);

	//ZoomIn Clicked
	connect(m_ZoomIn, SIGNAL(clicked()),
		otro, SLOT(RenderZoomIn())
		);
	m_GridLayout->addWidget(otro, 0, 4, 3, 6);
	setLayout(m_GridLayout);

	//ZoomOut Clicked
	connect(m_ZoomOut, SIGNAL(clicked()),
		otro, SLOT(RenderZoomOut())
		);
	m_GridLayout->addWidget(otro, 1, 4, 3, 6);
	setLayout(m_GridLayout);

	//ImageClicked
	connect(otro, SIGNAL(RGBValues(int, int, int, int,int,int)),
		this, SLOT(RGBLabel(int, int, int,int,int, int)));
	setLayout(m_GridLayout);

	//PenSetUp Clicked
	connect(m_PenSetUp, SIGNAL(clicked()),
		otro, SLOT(RenderPenSetUp()));

	//PenSetUpOff Clicked
	connect(m_PenSetUpOff, SIGNAL(clicked()),
		otro, SLOT(RenderPenSetUpOff()));



	// get n and d value from user in UI
	//connect(spinBox,SIGNAL(valueChanged (double)),otro,SLOT(updateDist(double)));
	//connect(slider,SIGNAL(valueChanged (int)),this,SLOT(cast(int)));
	//connect(this, SIGNAL(signalNeda(double)),otro, SLOT(updateDist(double)));
	connect(spinBox,SIGNAL(valueChanged (double)),otro,SLOT(updateDist(double)));
    	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue4spin()));
	connect(spinBox, SIGNAL(valueChanged(double)),this, SLOT(setValue4slider()));


	//connect(n1,SIGNAL(valueChanged (int)),this,SLOT(cast(int)));
	//connect(this, SIGNAL(signalNeda(double)),otro, SLOT(updaten1(double)));
	connect(spin1,SIGNAL(valueChanged (double)),otro,SLOT(updaten1(double)));
	//connect(n1, SIGNAL(valueChanged(int)),this, SLOT(setValue1spin()));
	//connect(spin1, SIGNAL(valueChanged(double)),this, SLOT(setValue1slider()));


	//connect(n2,SIGNAL(valueChanged (int)),this,SLOT(cast(int)));
	//connect(this, SIGNAL(signalNeda(double)),otro, SLOT(updaten2(double)));
	connect(spin2,SIGNAL(valueChanged (double)),otro,SLOT(updaten2(double)));
	//connect(n2, SIGNAL(valueChanged(int)),this, SLOT(setValue2spin()));
	//connect(spin2, SIGNAL(valueChanged(double)),this, SLOT(setValue2slider()));


	//connect(n3,SIGNAL(valueChanged (int)),this,SLOT(cast(int)));
	//connect(this, SIGNAL(signalNeda(double)),otro, SLOT(updaten3(double)));
	connect(spin3,SIGNAL(valueChanged (double)),otro,SLOT(updaten3(double)));
	//connect(n3, SIGNAL(valueChanged(int)),this, SLOT(setValue3spin()));
	//connect(spin3, SIGNAL(valueChanged(double)),this, SLOT(setValue3slider()));

	connect(spinIntensityMin,SIGNAL(valueChanged (double)),otro,SLOT(updateIMin(double)));
	connect(spinIntensityMax,SIGNAL(valueChanged (double)),otro,SLOT(updateIMax(double)));

	connect(rotSpin,SIGNAL(valueChanged (double)),otro,SLOT(updateAngle(double)));


}

void window::cast(int value)
{
	double neda = value;
	emit signalNeda(neda);
}

/*
void window::setValue1spin()
{
	spin1->setValue(n1->value());
}

void window::setValue1slider()
{
	n1->setValue(spin1->value());
}


void window::setValue2spin()
{
	spin2->setValue(n2->value());
}

void window::setValue2slider()
{
	n2->setValue(spin2->value());
}


void window::setValue3spin()
{
	spin3->setValue(n3->value());
}

void window::setValue3slider()
{
	n3->setValue(spin3->value());
}

*/

void window::setValue4spin()
{
	spinBox->setValue(slider->value());
}

void window::setValue4slider()
{
	slider->setValue(spinBox->value());
}


//Image Clicked
//Shows label in the upper left corner on the top of the image with the real x,y coordinates and the RGB values of the clicked pixel
void window::RGBLabel(int red, int green, int blue, int alpha, int xreal, int yreal)
{
	m_lblRGB->setText(QString("From the Original Image: x=%1 y=%2 , R=%3, G=%4, B=%5, A=%6")
		.arg(xreal)
		.arg(yreal)
		.arg(red)
		.arg(green)
		.arg(blue)
		.arg(alpha));
}



