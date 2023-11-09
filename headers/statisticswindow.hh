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
     * @brief Load the data related to users money to the charts
     */
    void load_money_data_to_charts(QMap<std::string, int> money_per_day,
                                   int total_money);

    /**
     * @brief Load the data related to users money from the database
     */
    void load_money_data_from_db();

    /**
     * @brief Load the data related to users games to the charts
     */
    void load_game_data_to_charts(QMap<std::string, int> wins_per_day,
                                  QMap<std::string, int> losses_per_day,
                                  int wins_all_time,
                                  int losses_all_time);

    /**
     * @brief Load the data related to users games from the database
     */
    void load_game_data_from_db();

private:
    Database *m_db;
    Ui::StatisticsWindow *ui;

    // Money related charts
    QtCharts::QChart *chart_money_;
    QtCharts::QChartView *chart_view_money_;
    QtCharts::QBarSeries *bar_series_money_;
    QStringList categories_money_;
    QLabel *total_money_label_;

    // Game related charts
    QtCharts::QChart *chart_games_;
    QtCharts::QChartView *chart_view_games_;
    QtCharts::QBarSeries *bar_series_games_;
    QStringList categories_games_;
    QLabel *total_rounds_label_;
};

#endif // STATISTICSWINDOW_HH
