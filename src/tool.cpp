#include "tool.h"


tool::tool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tool){
    ui->setupUi(this);
    type = cv::Vec3b(0,255,0);
    ui->t_grass->setChecked(true);
    connect(ui->lblMask,SIGNAL(mousePressed()),this,SLOT(mousePressd()));
    connect(ui->lblMask,SIGNAL(mousePos()),this,SLOT(mousePose()));
    connect(ui->lbl,SIGNAL(mousePressed()),this,SLOT(mousePressdOnImg()));
    connect(ui->lbl,SIGNAL(mousePos()),this,SLOT(mousePoseOnImg()));


    QShortcut * sh_next = new QShortcut(this);
    sh_next->setKey(Qt::Key_D);
    QObject::connect(sh_next, SIGNAL(activated()), this, SLOT(on_btn_Next_clicked()));

    QShortcut * sh_prev = new QShortcut(this);
    sh_prev->setKey(Qt::Key_A);
    QObject::connect(sh_prev, SIGNAL(activated()), this, SLOT(on_btn_Prev_clicked()));

    QShortcut * sh_save = new QShortcut(this);
    sh_save->setKey(Qt::Key_S);
    QObject::connect(sh_save, SIGNAL(activated()), this, SLOT(on_save_clicked()));

}

tool::~tool(){
    delete ui;
}

void tool::loadSample(int id){
    current = _dataSet.getSample(id);
    current.imRead();
    tool::suggestSegments();
    tool::showSample();
}

void tool::suggestSegments(){
    cv::Mat fw= current.getImg();
    cv::Mat img;
    fw.copyTo(img);
    if(ui->checkBox->isChecked()){
        egbs.applySegmentation(img, ui->k->value(), ui->v->value());
    }
    current.setSMask(img);
}

void tool::showSample(){

    cv::Mat img;
    current.getImg().copyTo(img);
    cv::Mat mask = current.getMask();
    cv::Mat sMask = current.getSMask();
    cv::Mat selmask = current.getSelectsMask();
    for(int i =0;i<img.rows;i++){
        for(int j = 0;j<img.cols;j++){
            if(mask.at<cv::Vec3b>(i,j)!=cv::Vec3b(0,0,0)){
                img.at<cv::Vec3b>(i,j)=mask.at<cv::Vec3b>(i,j);
            }
            if(selmask.at<cv::Vec3b>(i,j)!=cv::Vec3b(0,0,0)){
                img.at<cv::Vec3b>(i,j)=selmask.at<cv::Vec3b>(i,j);
            }
        }
    }
    pattern_planning(img);
    ui->lbl->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows
                                          ,img.step,QImage::Format_RGB888 )));
    ui->lblMask->setPixmap(QPixmap::fromImage(QImage(sMask.data,img.cols,img.rows
                                          ,img.step,QImage::Format_RGB888 )));
}

void tool::on_btn_Open_clicked(){
    QDir dir = QFileDialog::getExistingDirectory(this, tr("select directory"));
    QStringList filter = {"*.jpg","*.png"};
    foreach(QFileInfo item, dir.entryInfoList(filter) )
        {
            if(item.isDir())
                qDebug() << "Dir: " << item.absoluteFilePath();
            else if(item.isFile()){
//                qDebug() << "File: " << item.absoluteFilePath();
                QString filePath = dir.absolutePath();
                QString fileName = item.fileName();
                sample temp(filePath.toStdString(),fileName.toStdString());
                _dataSet.addSample(temp);
            }
        }
    if(_dataSet.getSize()>0){
        ui->lblMask->setEnabled(true);
        tool::loadSample(currentSample);
    }
}

void tool::on_btn_Next_clicked(){
    if(_dataSet.getSize()<1)
        return;
    currentSample = std::min(_dataSet.getSize()-1,currentSample+1);
    tool::loadSample(currentSample);
    clear_selectors();
    drawing_circle=false;
    drawing_line=false;
    drawing_polygon=false;
}

void tool::on_btn_Prev_clicked(){
    if(_dataSet.getSize()<1)
        return;
    currentSample = std::max(0,currentSample-1);
    tool::loadSample(currentSample);
    clear_selectors();
}
void tool::on_k_editingFinished(){
    tool::suggestSegments();
    tool::showSample();
}

void tool::on_v_editingFinished(){
    tool::suggestSegments();
    tool::showSample();
}

void tool::mousePressd(){
    cv::Mat sMask = current.getSMask();
    cv::Vec3b segment = sMask.at<cv::Vec3b>(ui->lblMask->y,ui->lblMask->x);
    if(ui->lblMask->left==true){
        current.addSegment(segment,type);
    }else{
        current.removeSegment(segment);
    }
    showSample();

}

void tool::mousePose(){
    cv::Mat sMask = current.getSMask();
    cv::Vec3b segment = sMask.at<cv::Vec3b>(ui->lblMask->y,ui->lblMask->x);
    cv::Mat color(ui->color->height(),ui->color->width(),CV_8UC3,cv::Scalar(segment[0],segment[1],segment[2]));

    ui->color->setPixmap(QPixmap::fromImage(QImage(color.data,color.cols,color.rows
                                                   ,color.step,QImage::Format_RGB888 )));
}

void tool::mousePressdOnImg()
{
    if(ui->s_box->isChecked()){
        selector.selectBox(cv::Point(ui->lbl.x,ui->lbl.y),type);
    }else if(ui->s_polygon->isChecked()){
        selector.selectPolygon(cv::Point(ui->lbl.x,ui->lbl.y),type);
    }else if(ui->s_line->isChecked()){
        selector.selectLine(cv::Point(ui->lbl.x,ui->lbl.y),type);
    }





    if(ui->s_circle->isChecked()){
        cv::Point2d M_pos(std::max(std::min(ui->lbl->x,ui->lbl->width()-4),0),ui->lbl->y);
        if(ui->lbl->left==true){
            if(drawing_circle==false){
                Cirs.push_back(Circle());
                Cirs[Cirs.size()-1].set_radius(0);
                drawing_circle=true;
                Cirs[Cirs.size()-1].is_drawing(true);
                Cirs[Cirs.size()-1].set_centre(M_pos);
            }
            else {
                cv::Mat selmask=current.getSelectsMask();
                Cirs[Cirs.size()-1].set_radius(sqrt(pow(Cirs[Cirs.size()-1].get_centre().y-ui->lbl->y,2)+pow(Cirs[Cirs.size()-1].get_centre().x-ui->lbl->x,2)));
                Cirs[Cirs.size()-1].is_drawing(false);
                Cirs[Cirs.size()-1].draw(&selmask,type,-1);
                showSample();
                drawing_circle=false;
            }
        }
        else if(Cirs.size()>0 && drawing_circle==false){
            cv::Mat selmask=current.getSelectsMask();
            Cirs[Cirs.size()-1].clean(&selmask);
            Cirs.pop_back();
            showSample();
        }
    }
    else if(ui->s_polygon->isChecked()){
        cv::Point2d M_pos(std::max(std::min(ui->lbl->x,ui->lbl->width()-4),0),ui->lbl->y);
        if(ui->lbl->left==true){
            if(drawing_polygon==false){
                Pols.push_back(Polygon());
                Pols[Pols.size()-1].is_drawing(true);
                Pols[Pols.size()-1].add_vertex(M_pos);
                drawing_polygon=true;
            }
            else if(7 < sqrt(pow(M_pos.y-Pols[Pols.size()-1].get_vertices()[0].y,2)+pow(M_pos.x-Pols[Pols.size()-1].get_vertices()[0].x,2))){
                Pols[Pols.size()-1].add_vertex(M_pos);
            }
            else{
                cv::Mat selmask=current.getSelectsMask();
                Pols[Pols.size()-1].draw(&selmask,type);
                Pols[Pols.size()-1].is_drawing(false);
                showSample();
                drawing_polygon=false;
            }
        }
        else if(drawing_polygon==true){
            if(Pols[Pols.size()-1].get_vertices().size()!=1){
                Pols[Pols.size()-1].remove_vertex(1);
            }
            else if(Pols.size()>0){
                cv::Mat selmask=current.getSelectsMask();
                Pols[Pols.size()-1].clean(&selmask);
                Pols.pop_back();
                drawing_polygon=false;
            }
            showSample();
        }
        else if(Pols.size()>0){
            cv::Mat selmask=current.getSelectsMask();
            Pols[Pols.size()-1].clean(&selmask);
            Pols.pop_back();
            showSample();
        }
    }
    else if(ui->s_line->isChecked()){
        cv::Point2d M_pos(std::max(std::min(ui->lbl->x,ui->lbl->width()-4),0),ui->lbl->y);
        if(ui->lbl->left){
            if(drawing_line==false){
                Lines.push_back(Line());
                Lines[Lines.size()-1].set_point1(M_pos);
                drawing_line=true;
            }
            else{
                cv::Mat selmask=current.getSelectsMask();
                Lines[Lines.size()-1].set_point2(M_pos);
                Lines[Lines.size()-1].draw(&selmask,type,ui->thickness->value());
                drawing_line=false;
                showSample();
            }
        }
        else if(drawing_line==false && Lines.size()>0){
            cv::Mat selmask=current.getSelectsMask();
            Lines[Lines.size()-1].clean(&selmask);
            Lines.pop_back();
            for(int i=0;i<int(Lines.size());i++)
                Lines[i].draw(&selmask,cv::Scalar(Lines[i].get_color()),Lines[i].get_thickness());
            showSample();
        }
        else if(Lines.size()>0){
            Lines.pop_back();
            drawing_line=false;
            showSample();
        }
    }
}
void tool::mousePoseOnImg(){
    if(drawing_circle || drawing_polygon || drawing_line)
        showSample();
}
void tool::on_t_lines_clicked(){
    type = cv::Vec3b(255,255,255);
}

void tool::on_t_ball_clicked(){
    type = cv::Vec3b(0,0,255);
}

void tool::on_t_grass_clicked(){
    type = cv::Vec3b(0,255,0);
}

void tool::on_t_goal_clicked(){
    type = cv::Vec3b(255,255,0);
}


void tool::on_save_clicked(){
    if(_dataSet.getSize()<1)
        return;
    _dataSet.setSample(currentSample,current);
    cv::Mat selmask=current.getSelectsMask();
    _dataSet.saveSample(currentSample);
    Cirs.clear();
    Pols.clear();
    Lines.clear();
    on_btn_Next_clicked();
}

void tool::on_t_penalty_clicked(){
    type = cv::Vec3b(255,0,0);
}

void tool::on_radioButton_clicked()
{
    type=cv::Vec3b(0,255,255);
}

void tool::pattern_planning(cv::Mat img){
    if(drawing_circle){
        if(Cirs[Cirs.size()-1].is_drawing()){
            cv::circle(img,Cirs[Cirs.size()-1].get_centre(),sqrt(pow(Cirs[Cirs.size()-1].get_centre().y-ui->lbl->y,2)+pow(Cirs[Cirs.size()-1].get_centre().x-ui->lbl->x,2)),cv::Scalar(0,0,255));
        }
    }
    else if(drawing_polygon){
        cv::circle(img,Pols[int(Pols.size())-1].get_vertices()[0],7,(cv::Scalar(238,130,238)),1);
        for(int j=0;j<int(Pols[int(Pols.size())-1].get_vertices().size())-1;j++){
            cv::line(img,Pols[Pols.size()-1].get_vertices()[j],Pols[Pols.size()-1].get_vertices()[j+1],cv::Scalar(255,0,0),2);
        }
        if(Pols[Pols.size()-1].is_drawing())
            cv::line(img,Pols[Pols.size()-1].get_vertices()[Pols[Pols.size()-1].get_vertices().size()-1],cv::Point2d(std::min(ui->lbl->x,ui->lbl->width()-4),ui->lbl->y),cv::Scalar(255,0,0),2);
        else{
            cv::line(img,Pols[Pols.size()-1].get_vertices()[Pols[Pols.size()-1].get_vertices().size()-1],Pols[Pols.size()-1].get_vertices()[0],cv::Scalar(255,0,0),2);
        }
    }
    else if(drawing_line){
        cv::line(img,Lines[Lines.size()-1].get_point1(),cv::Point2d(ui->lbl->x,ui->lbl->y),type,ui->thickness->value());
    }
}

void tool::clear_selectors(){
    Lines.clear();
    Pols.clear();
    Cirs.clear();
    drawing_circle=false;
    drawing_line=false;
    drawing_polygon=false;
}
