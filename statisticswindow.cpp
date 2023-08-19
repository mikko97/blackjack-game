#include "statisticswindow.hh"
#include "ui_statisticswindow.h"

StatisticsWindow::StatisticsWindow(Database *db, QWidget *parent) :
    QWidget(parent),
    m_db(db),
    ui(new Ui::StatisticsWindow)
{
    ui->setupUi(this);

    QFont right_layout_font("Tahoma", 16, QFont::DemiBold);

    // Create the bar chart for displaying the money related data
    bar_series_money_ = new QtCharts::QBarSeries();
    total_money_label_ = new QLabel(this);
    total_money_label_->setFont(right_layout_font);
    total_money_label_->setStyleSheet("padding: 22px; color: white; border-style: dashed; border-width: 8px; border-color: white");
    load_money_data();

    chart_money_ = new QtCharts::QChart();
    chart_money_->addSeries(bar_series_money_);

    chart_money_->setTitle("Money won last X days");
    chart_money_->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis *axis_x_money = new QtCharts::QBarCategoryAxis();
    axis_x_money->append(categories_money_);
    chart_money_->addAxis(axis_x_money, Qt::AlignBottom);
    bar_series_money_->attachAxis(axis_x_money);

    QtCharts::QValueAxis *axis_y_money = new QtCharts::QValueAxis();
    chart_money_->addAxis(axis_y_money, Qt::AlignLeft);
    bar_series_money_->attachAxis(axis_y_money);

    chart_money_->legend()->setVisible(true);
    chart_money_->legend()->setAlignment(Qt::AlignBottom);

    chart_view_money_ = new QtCharts::QChartView(chart_money_);
    chart_view_money_->setRenderHint(QPainter::Antialiasing);


    // Create the bar chart for displaying the game related data
    bar_series_games_ = new QtCharts::QBarSeries();
    total_rounds_label_ = new QLabel(this);
    total_rounds_label_->setStyleSheet("padding: 22px; color: white; border-style: dashed; border-width: 8px; border-color: white");
    total_rounds_label_->setFont(right_layout_font);
    load_game_data();

    chart_games_ = new QtCharts::QChart();
    chart_games_->addSeries(bar_series_games_);
    chart_games_->setTitle("Rounds won and lost last X days");
    chart_games_->setAnimationOptions(QtCharts::QChart::SeriesAnimations);

    QtCharts::QBarCategoryAxis *axis_x_games = new QtCharts::QBarCategoryAxis();
    axis_x_games->append(categories_games_);
    chart_games_->addAxis(axis_x_games, Qt::AlignBottom);
    bar_series_games_->attachAxis(axis_x_games);

    QtCharts::QValueAxis *axis_y_games = new QtCharts::QValueAxis();
    chart_games_->addAxis(axis_y_games, Qt::AlignLeft);
    bar_series_games_->attachAxis(axis_y_games);

    chart_games_->legend()->setVisible(true);
    chart_games_->legend()->setAlignment(Qt::AlignBottom);

    chart_view_games_ = new QtCharts::QChartView(chart_games_);
    chart_view_games_->setRenderHint(QPainter::Antialiasing);

    // Create the left-hand side layout
    QVBoxLayout *left_layout = new QVBoxLayout;
    left_layout->addWidget(chart_view_money_);
    left_layout->addWidget(chart_view_games_);

    // Create the right-hand side layout
    QVBoxLayout *right_layout = new QVBoxLayout;
    right_layout->addWidget(total_money_label_);
    right_layout->addWidget(total_rounds_label_);

    // Create the main layout
    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout->addLayout(left_layout);
    main_layout->addLayout(right_layout);

    setStyleSheet("background-color: #008080");
    setLayout(main_layout);

}

void StatisticsWindow::load_money_data() {
    QMap<QDateTime, int> money_per_day = m_db->fetch_total_money_per_day();
    QtCharts::QBarSet *set_money_won = new QtCharts::QBarSet("Money won");
    QtCharts::QBarSet *set_money_lost = new QtCharts::QBarSet("Money lost");

    int total_money = 0;

    for (const QDateTime &day : money_per_day.keys()) {
        int total_money_day = money_per_day.value(day);
        if(total_money_day>0) {
            *set_money_won << total_money_day;
            *set_money_lost << 0;
        }
        else if(total_money_day<0) {
            *set_money_lost << -total_money_day;
            *set_money_won << 0;
        }
        categories_money_.append(day.toString("ddd MMM yyyy"));
        total_money += total_money_day;
    }
    set_money_won->setColor(Qt::green);
    set_money_lost->setColor(Qt::red);
    bar_series_money_->append(set_money_won);
    bar_series_money_->append(set_money_lost);

    total_money_label_->setText(QString("Total Money Won: %1").arg(total_money)+"$");
}

void StatisticsWindow::load_game_data() {
    QMap<QDateTime, int> wins_per_day = m_db->fetch_total_wins_per_day();
    QMap<QDateTime, int> losses_per_day = m_db->fetch_total_losses_per_day();
    QtCharts::QBarSet *set_won = new QtCharts::QBarSet("Rounds won");
    QtCharts::QBarSet *set_lost = new QtCharts::QBarSet("Rounds lost");
    QMap<QDateTime, int> map_with_fewer_days;
    QMap<QDateTime, int> map_with_more_days;

    if (wins_per_day.count() < losses_per_day.count()) {
        map_with_fewer_days = wins_per_day;
        map_with_more_days = losses_per_day;
    }

    else if(wins_per_day.count() > losses_per_day.count()){
        map_with_fewer_days = losses_per_day;
        map_with_more_days = wins_per_day;
    }

    else {
        map_with_more_days = wins_per_day;
    }

    int total_rounds_won = 0;
    int total_rounds_lost = 0;

    for (const QDateTime &day : map_with_more_days.keys()) {
        categories_games_.append(day.toString("ddd MMM yyyy"));
        if(wins_per_day.contains(day)) {
            int rounds_won_day = wins_per_day.value(day);
            *set_won << rounds_won_day;
            total_rounds_won += rounds_won_day;

        }
        else {
            *set_won << 0;
        }

        if(losses_per_day.contains(day)) {
            int rounds_lost_day = losses_per_day.value(day);
            *set_lost << rounds_lost_day;
            total_rounds_lost += rounds_lost_day;
        }
        else {
            *set_lost << 0;
        }
    }

    set_won->setColor(Qt::green);
    set_lost->setColor(Qt::red);
    bar_series_games_->append(set_won);
    bar_series_games_->append(set_lost);

    total_rounds_label_->setText(QString("Total Rounds Won: %1\n\nTotal Rounds Lost: %2")
                                 .arg(total_rounds_won).arg(total_rounds_lost));
}




