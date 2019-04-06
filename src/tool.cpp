#include "tool.h"

tool::tool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tool){

    ui->setupUi(this);

    type = cv::Vec3b(0,255,0);

    ui->t_grass->setChecked(true);
    ui->s_line->setChecked(true);

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

void tool::showAnnotation(cv::Mat &img){
    if(selector.is_drawing()){
        if(ui->s_box->isChecked()){
            cv::rectangle(img,cv::Point(selector.tBox.box.x,selector.tBox.box.y),cv::Point(ui->lblMask->x,ui->lblMask->y),cv::Scalar(255,255,255));
        }
        else if(ui->s_polygon->isChecked()){
            std::vector<cv::Point>::iterator pt_it = selector.tPolygons.begin();
            for(;pt_it<selector.tPolygons.end();pt_it++){
                cv::line(img,*pt_it,*(pt_it+1),cv::Scalar(255,255,255));
            }
            cv::line(img,*(pt_it+1),cv::Point(ui->lblMask->x,ui->lblMask->y),cv::Scalar(255,255,255));
        }
        else if(ui->s_line->isChecked()){
            cv::line(img,selector.tLine.p1,cv::Point(ui->lblMask->x,ui->lblMask->y),cv::Scalar(255,255,255));
        }
    }
    else{
        for(std::vector<bbox>::iterator bbox_it = selector.objects.begin();bbox_it<selector.objects.end();bbox_it++){
            cv::rectangle(img,bbox_it->box,cv::Scalar(255,255,255));
        }
        for(std::vector<Polygon>::iterator pol_it = selector.polygons.begin();pol_it<selector.polygons.end();pol_it++){
            for(Polygon::iterator pt_it = pol_it->begin() ; pt_it<(pol_it->end()-1);pt_it++){
                cv::line(img,*pt_it,*(pt_it+1),cv::Scalar(255,255,255));
            }
        }
        for(std::vector<Line>::iterator line_it=selector.lines.begin(); line_it<selector.lines.end(); line_it++){
            cv::line(img,line_it->p1,line_it->p2,cv::Scalar(255,255,255));
        }
    }
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
    showAnnotation(img);

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
}

void tool::on_btn_Prev_clicked(){
    if(_dataSet.getSize()<1)
        return;
    currentSample = std::max(0,currentSample-1);
    tool::loadSample(currentSample);
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
        current.setAnnotation(segment,type);
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

void tool::mousePressdOnImg(){
    if(ui->lblMask->left){
      if(ui->s_box->isChecked()){
        selector.selectBox(ui->lbl->pos,classType);
      }else if(ui->s_polygon->isChecked()){
        selector.selectPolygon(ui->lbl->pos,classType);
      }else if(ui->s_line->isChecked()){
        selector.selectLine(ui->lbl->pos,classType);
      }
    if(!selector.is_drawing())
      showSample();
    }
    else{
      if(ui->s_box->isChecked()){
        selector.removeBox(ui->lbl->pos);
      }
      showSample();
    }
}
void tool::mousePoseOnImg(){
  //if(selector.is_drawing())
    //showSample();
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
    on_btn_Next_clicked();
}

void tool::on_t_penalty_clicked(){
    type = cv::Vec3b(255,0,0);
}

void tool::on_radioButton_clicked()
{
    type=cv::Vec3b(0,255,255);
}
