#ifndef STATISTICSWINDOW_HH
#define STATISTICSWINDOW_HH

#include "database.hh"

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class StatisticsWindow; }
QT_END_NAMESPACE

class StatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWindow(Database *db, QWidget *parent = nullptr);

    /**
     * @brief Load the data related to users money
     */
    void load_money_data();

private:
    Database *m_db;
    Ui::StatisticsWindow *ui;
    QtCharts::QChartView *chart_view_;
    QtCharts::QBarSet *bar_set_;
    QtCharts::QBarSeries *bar_series_;
    QStringList categories_;
    QtCharts::QChart *chart_;
};

#endif // STATISTICSWINDOW_HH
