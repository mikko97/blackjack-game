#include "statisticswindow.hh"
#include "ui_statisticswindow.h"

StatisticsWindow::StatisticsWindow(Database *db, QWidget *parent) :
    QWidget(parent),
    m_db(db),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);

    bar_series_ = new QtCharts::QBarSeries();
    load_money_data();

    chart_ = new QtCharts::QChart();
    chart_->addSeries(bar_series_);
    chart_->setTitle("Money balance history");
    chart_->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories_);
    chart_->addAxis(axisX, Qt::AlignBottom);
    bar_series_->attachAxis(axisX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    chart_->addAxis(axisY, Qt::AlignLeft);
    bar_series_->attachAxis(axisY);

    chart_->legend()->setVisible(true);
    chart_->legend()->setAlignment(Qt::AlignBottom);

    chart_view_ = new QtCharts::QChartView(chart_);
    chart_view_->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(chart_view_);
    setLayout(layout);
}

void StatisticsWindow::load_money_data() {
    QMap<QDateTime, int> money_per_day = m_db->fetch_total_money_per_day();
    QtCharts::QBarSet *set = new QtCharts::QBarSet("Money won");

    for (const QDateTime &day : money_per_day.keys()) {
        int total_money = money_per_day.value(day);
        *set << total_money;
        set->color().setNamedColor("green");
        categories_.append(day.toString("ddd MMM yyyy"));

        //line_series_->append(QPoint(total_money, day.toMSecsSinceEpoch()));
        qDebug() << "Date: " << day.toString("ddd MMM yyyy") << "Total Money: " << total_money;
    }
    bar_series_->append(set);
}




