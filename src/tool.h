#ifndef TOOL_H
#define TOOL_H

#include "QMainWindow"
#include "QFileDialog"
#include "QShortcut"
#include "dataset.h"
#include "QDebug"
#include "QDir"
#include "ui_tool.h"
#include "selector.h"
#include "EGBS.h"

namespace Ui {
class tool;
}

class tool : public QMainWindow
{
    Q_OBJECT

public:
    explicit tool(QWidget *parent = 0);
    ~tool();
    void showSample();
    void loadSample();
    void suggestSegments();
    void showAnnotation(cv::Mat& img);
private slots:
    void on_btn_Open_clicked();

    void on_btn_Next_clicked();

    void on_btn_Prev_clicked();

    void on_k_editingFinished();

    void on_v_editingFinished();

    void mousePressd();

    void mousePose();

    void mousePressdOnImg();

    void mousePoseOnImg();

    void on_t_lines_clicked();

    void on_t_ball_clicked();

    void on_t_grass_clicked();

    void on_t_goal_clicked();

    void on_save_clicked();

    void on_t_penalty_clicked();

    void on_radioButton_clicked();
private:
    Ui::tool *ui;
    dataSet _dataSet;
    EGBS egbs;
    cv::Vec3b type;
    int classType;
    void rm_selectors();


};

#endif // TOOL_H
