// mainwindow.cpp
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the main window
    setFixedSize(800, 1000);

    // Set the background image
    QString imagePath = "C:/Users/shahe/OneDrive - Aiila Innovations Pvt Ltd/Projects/RadarDisplay/Maps.png";
    backgroundPixmap.load(imagePath);

    // Seed the random number generator
    srand(QTime::currentTime().msec());

    // Connect the timer to the update function
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(2000);  // Refresh every 100 milliseconds
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // Create a QPainter object to perform painting operations
    QPainter painter(this);

    // Set up the pen for drawing axis and labels
    QPen axisPen(Qt::black);
    axisPen.setWidth(2);
    QFont axisLabelFont("Arial", 10);
    axisLabelFont.setBold(true);
    axisLabelFont.setItalic(false);

    // Draw the background image
    painter.drawPixmap(0, 0, width(), height(), backgroundPixmap);

    // Define the radar center coordinates
    int radarCenterX = width() / 2;
    int radarCenterY = height() / 2;

    // Draw axis lines
    painter.setPen(axisPen);
    painter.drawLine(radarCenterX, 0, radarCenterX, height());  // Vertical axis
    painter.drawLine(0, radarCenterY, width(), radarCenterY);  // Horizontal axis

    // Draw axis labels
    QString xAxisLabel = "X (pixels)";
    QString yAxisLabel = "Y (pixels)";
    painter.setFont(axisLabelFont);
    painter.setPen(Qt::black);
    painter.drawText(QPoint(radarCenterX - 20, height() - 10), xAxisLabel);
    painter.drawText(QPoint(10, radarCenterY - 5), yAxisLabel);

    // Draw equidistant rings
    int ringCount = 8;  // Number of rings
    int ringRadius = 50;  // Initial radius for the first ring

    for (int i = 0; i < ringCount; ++i) {
        painter.setPen(axisPen);
        painter.drawEllipse(QPoint(radarCenterX, radarCenterY), ringRadius, ringRadius);

        // Draw the ring value on the ring
        QString ringLabel = QString::number(ringRadius) + " pixels";
        painter.setFont(axisLabelFont);
        painter.setPen(Qt::black);
        painter.drawText(QPoint(radarCenterX - ringRadius, radarCenterY - ringRadius), ringLabel);

        ringRadius += 50;  // Increase the radius for the next ring
    }

    // Draw moving targets
    int targetCount = 5;  // Number of targets
    int targetRadius = 10;  // Radius of the target

    for (int i = 0; i < targetCount; ++i) {
        // Generate random distance for the target
        int targetDistance = rand() % 400 + 50;  // Random distance between 50 and 450 pixels

        // Calculate target coordinates based on distance and angle
        double angle = i * 72.0;  // Angle between each target (360 degrees divided by 5)
        int targetX = radarCenterX + qCos(qDegreesToRadians(angle)) * targetDistance;
        int targetY = radarCenterY + qSin(qDegreesToRadians(angle)) * targetDistance;

        // Get random color for the target
        QColor targetColor = getRandomColor();

        painter.setBrush(targetColor);
        painter.setPen(Qt::NoPen);  // No outline for targets

        if (i < 2) {
            // Draw a triangle for the first two targets
            QPolygonF triangle;
            triangle << QPointF(targetX, targetY - targetRadius);
            triangle << QPointF(targetX - targetRadius, targetY + targetRadius);
            triangle << QPointF(targetX + targetRadius, targetY + targetRadius);
            painter.drawPolygon(triangle);
        } else {
            // Draw a circle for the remaining targets
            painter.drawEllipse(QPoint(targetX, targetY), targetRadius, targetRadius);
        }
    }
}

QColor MainWindow::getRandomColor()
{
    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;

    return QColor(red, green, blue);
}


