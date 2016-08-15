#include <QtWidgets/QLabel> 
#include <QtWidgets/QMainWindow> 
#include <QtWidgets/QPushButton> 
#include <QtWidgets/QGridLayout>
#include <QImage>
#include <QSlider>
#include <QGroupBox>
#include <QDoubleSpinBox>



class window : public QWidget
{
	Q_OBJECT;
public:
	window(QWidget* parent = NULL);

signals:
	void signalNeda(double);

public slots:
	void RGBLabel(int, int, int,int,int, int);
	//void setValue1spin();
	//void setValue1slider();
	//void setValue2spin();
	//void setValue2slider();
	//void setValue3spin();
	//void setValue3slider();
	void setValue4spin();
	void setValue4slider();
	//void tabeAlaki(int);
	void cast(int);
private:
	void setupWindow();

	//input widgets as member variables to access them later
	QPushButton* m_Load;
	QPushButton* m_Save;
	QPushButton* m_ZoomIn;
	QPushButton* m_ZoomOut;
	QPushButton* m_PenSetUp;
	QPushButton* m_PenSetUpOff;
	QPixmap* m_I;// = new QPixmap();
	QLabel* m_lblI;// = new QLabel();
	QGridLayout* m_GridLayout;
	QLabel* m_lblRGB;

	QSlider* slider;
	QLabel* sliderLabel;
	QDoubleSpinBox *spinBox;

//	QGroupBox* IntensityRangeGroup();

	QLabel* nLabel;
	QSlider* n1;
	QDoubleSpinBox *spin1;
	QSlider* n2;
	QDoubleSpinBox *spin2;
	QSlider* n3;
	QDoubleSpinBox *spin3;
	QGroupBox* mpr; 
	QHBoxLayout* mprLayout;

	QLabel* IntensityRange;
	QDoubleSpinBox *spinIntensityMin;
	QDoubleSpinBox *spinIntensityMax;

	QLabel* rotLabel;
	QDoubleSpinBox* rotSpin;

};

