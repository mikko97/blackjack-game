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
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QLabel>

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

    /**
     * @brief Load the data related to users games
     */
    void load_game_data();

private:
    Database *m_db;
    Ui::StatisticsWindow *ui;

    QtCharts::QChart *chart_money_;
    QtCharts::QChartView *chart_view_money_;
    QtCharts::QBarSeries *bar_series_money_;
    QStringList categories_money_;

    QtCharts::QChart *chart_games_;
    QtCharts::QChartView *chart_view_games_;
    QtCharts::QBarSeries *bar_series_games_;
    QStringList categories_games_;

    QLabel *total_money_label_;
    QLabel *total_rounds_label_;
};

#endif // STATISTICSWINDOW_HH
