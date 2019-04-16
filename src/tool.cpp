#include "tool.h"
typedef std::pair<int , cv::Vec3b> label;
tool::tool(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::tool){

  ui->setupUi(this);

  type = 1;
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

  classColore.insert(label(0,cv::Vec3b(0,0,0)));       //background
  classColore.insert(label(1,cv::Vec3b(255,0,0)));     //lines
  classColore.insert(label(2,cv::Vec3b(0,255,0)));     //grass

  classColore.insert(label(3,cv::Vec3b(0,0,255)));     //ball
  classColore.insert(label(4,cv::Vec3b(255,255,0)));     //robot

}

tool::~tool(){
  delete ui;
}

void tool::loadSample(){
  _dataSet.current->imRead();
  _dataSet.current->suggestSegments(egbs,ui->k->value(),ui->v->value());
  tool::showSample();
}


void tool::showAnnotation(cv::Mat &img){
  if(_dataSet.current->is_drawing()){
    if(ui->s_box->isChecked()){
      cv::rectangle(img, cv::Point(_dataSet.current->tBox.box.x, _dataSet.current->tBox.box.y),
        ui->lbl->pos, classColore.at(type), 2);
      }
      else if(ui->s_polygon->isChecked()){
        Polygon::iterator pt_it = _dataSet.current->tPolygons.begin();
        for(;pt_it < _dataSet.current->tPolygons.end()-1;pt_it++)
          cv::line(img, *pt_it, *(pt_it+1), classColore.at(type));
        cv::line(img,*(pt_it), ui->lbl->pos, classColore.at(type));
      }
      else if(ui->s_line->isChecked()){
        cv::line(img,_dataSet.current->tLine.p1,ui->lbl->pos,classColore.at(type));
      }
    }else{
    for(std::vector<bbox>::iterator bbox_it = _dataSet.current->objects.begin();bbox_it<_dataSet.current->objects.end();bbox_it++){
      cv::rectangle(img,bbox_it->box,classColore.at(bbox_it->type),2);
    }
    for(std::vector<Polygon>::iterator pol_it = _dataSet.current->polygons.begin();pol_it<_dataSet.current->polygons.end();pol_it++){
      for(Polygon::iterator pt_it = pol_it->begin() ; pt_it < pol_it->end()-1;pt_it++){
        cv::line(img,*pt_it,*(pt_it+1),pol_it->type);
      }
    }
    for(std::vector<Line>::iterator line_it=_dataSet.current->lines.begin(); line_it<_dataSet.current->lines.end(); line_it++){
      cv::line(img,line_it->p1,line_it->p2,line_it->type);
    }
  }
}

void tool::showSegmentaion(cv::Mat & img){
    _dataSet.current->generateMask();
    std::cout<<"de"<<std::endl;
    _dataSet.current->segmentaions.copyTo(img);
    std::cout<<"deds"<<std::endl;
}

void tool::showSample(){
  cv::Mat img;
  _dataSet.current->getImg().copyTo(img);
  if(ui->showMask->isChecked()){
      showSegmentaion(img);
  }else{
    showAnnotation(img);
  }

  ui->lbl->setPixmap(QPixmap::fromImage(QImage(img.data,img.cols,img.rows,img.step,QImage::Format_RGB888 )));
  ui->lblMask->setPixmap(QPixmap::fromImage(QImage(_dataSet.current->suggstedSegments.data,img.cols,img.rows,img.step,QImage::Format_RGB888 )));
}


void tool::on_btn_Open_clicked(){
  QDir dir = QFileDialog::getExistingDirectory(this, tr("select directory"));
  QStringList filter = {"*.jpg","*.png"};
  foreach(QFileInfo item, dir.entryInfoList(filter) ){
    if(item.isDir())
      qDebug() << "Dir: " << item.absoluteFilePath();
    else if(item.isFile()){
      qDebug() << "File: " << item.absoluteFilePath();
      QString filePath = dir.absolutePath();
      QString fileName = item.fileName();
      Sample temp(filePath.toStdString(),fileName.toStdString());
      _dataSet.addSample(temp);
    }
  }
  if(_dataSet.getSize()>0){
    _dataSet.initDataSet();
    ui->lblMask->setEnabled(true);
    ui->lbl->setEnabled(true);
    tool::loadSample();
  }
}

void tool::on_btn_Next_clicked(){
  if(_dataSet.getSize()<1)
    return;
  _dataSet.next();
  tool::loadSample();
}

void tool::on_btn_Prev_clicked(){
  if(_dataSet.getSize()<1)
    return;
  _dataSet.prev();
  tool::loadSample();
}

void tool::on_save_clicked(){
  if((int)_dataSet.getSize()<1){
    return;
  }
    on_btn_Next_clicked();
}

void tool::on_k_editingFinished(){
  _dataSet.current->suggestSegments(egbs,ui->k->value(),ui->v->value());
  tool::showSample();
}

void tool::on_v_editingFinished(){
  _dataSet.current->suggestSegments(egbs,ui->k->value(),ui->v->value());
  tool::showSample();
}

void tool::mousePressd(){
  if(ui->lblMask->left==true){
    _dataSet.current->selectSegment(ui->lblMask->pos, classColore.at(type) );
  }else{
    _dataSet.current->removeSegment(ui->lblMask->pos, classColore.at(type));
  }
  showSample();
}

void tool::mousePose(){
  cv::Mat sMask = _dataSet.current->getSMask();
  cv::Vec3b segment = sMask.at<cv::Vec3b>(ui->lblMask->y,ui->lblMask->x);
  cv::Mat color(ui->color->height(),ui->color->width(),CV_8UC3,cv::Scalar(segment[0],segment[1],segment[2]));
  ui->color->setPixmap(QPixmap::fromImage(QImage(color.data,color.cols,color.rows
                                                 ,color.step,QImage::Format_RGB888 )));
}


void tool::mousePressdOnImg(){
  if(ui->lbl->left){
    if(ui->s_box->isChecked()){
      _dataSet.current->selectBox(ui->lbl->pos,type);
    }else if(ui->s_polygon->isChecked()){
      _dataSet.current->selectPolygon(ui->lbl->pos,classColore.at(type));
    }else if(ui->s_line->isChecked()){
      _dataSet.current->selectLine(ui->lbl->pos,classColore.at(type));
    }
  }
  else{
    if(ui->s_box->isChecked()){
      _dataSet.current->removeBox(ui->lbl->pos);
    }
    else if(ui->s_polygon->isChecked()){
      _dataSet.current->removePolygon(ui->lbl->pos);
    }
  }
  showSample();
}
void tool::mousePoseOnImg(){
  if(_dataSet.current->is_drawing())
    showSample();
}


void tool::on_t_lines_clicked(){
  type = 1;
}

void tool::on_t_ball_clicked(){
  type = 3;
}

void tool::on_t_grass_clicked(){
  type = 2;
}

void tool::on_t_bg_clicked(){
    type = 0;
}

void tool::on_t_robot_clicked(){
    type = 4;
}






void tool::on_showMask_clicked(){
    showSample();
}
