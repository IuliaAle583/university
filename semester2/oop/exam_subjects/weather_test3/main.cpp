#include "weather3.h"
#include <QtWidgets/QApplication>
#include "Domain.h"
#include "Repository.h"
#include "Service.h"
#include "GUI.h"
/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repository;
    Service service(repository);
    GUI gui(service);

    gui.show();
    return a.exec();
}*/
#include <QApplication>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
#include <QtWidgets/QMainWindow>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // Set up data
    QBarSet* set0 = new QBarSet("Jane");
    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    QBarSet* set1 = new QBarSet("John");
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;

    // Create series and add sets
    QBarSeries* series = new QBarSeries();
    series->append(set0);
    series->append(set1);

    // Create chart and add series
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple Bar Chart Example");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Create chart view with chart
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Create main window and set chart view as central widget
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    return app.exec();
}

