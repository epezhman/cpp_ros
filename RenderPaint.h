#include <QtWidgets/QLabel>
#include <QImage>
#include <QPaintEvent>
#include <QtWidgets/QGridLayout>
#include <QComboBox>
#include <QSpinBox>
#include "MHDHandler.h"



class RenderPaint : public QWidget
{
	Q_OBJECT;

public:
	RenderPaint(QWidget* parent);
	void SetImage(QImage* image);
	void mousePressEvent(QMouseEvent* event);

public slots:
	void RenderLoad();
	void RenderSave();
	void RenderZoomIn();
	void RenderZoomOut();
	void RenderPenSetUp();
	void RenderPenSetUpOn();
	void RenderPenSetUpOff();
	void Drawing();
	void LoadImage();
	void SaveImage();
	void updateDist(double);
	void updaten1(double);
	void updaten2(double);
	void updaten3(double);
	void updateParam();
	void updateIMin(double);
	void updateIMax(double);
	void updateAngle(double);

signals:
	void RGBValues(int, int, int, int, int, int);

protected:
	void paintEvent(QPaintEvent* pe) override;

private:
	Volume* MyVolume;
	//Volume ned();
	MHDHandler MyHandler;
	QImage* m_RawImg;
	QImage* m_Img;
	QSize m_RealSize;
	QSize m_size;
	int m_clickX;
	int m_clickY;
	int m_realx;
	int m_realy;
	bool m_paint;

	float distance;
	float n1;
	float n2;
	float n3;

	float iMin;
	float iMax;

	double theta;

	QComboBox* cbColor;
	QSpinBox* sbSize;
	QRgb m_RGBValue;
	QLineEdit* lePath;
	QLineEdit* leSavePath;

};

