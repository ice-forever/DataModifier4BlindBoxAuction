#include "modmenu.h"
#include "ui_modmenu.h"

typedef struct
{
    int uid;
    QString name;
    int score;
    int use;
    bool *get;
    int level;
} USERDATAwithMOD;
typedef struct
{
    QString name;
    int  id;
} Achievement;
QVector <Achievement> achivector;
QVector <USERDATAwithMOD> datamodvector;
int numberofachievement;
int MaxAchievementID;
QString backupdir="操作备份";
void MODmenu::checkfirstrun()
{
    QDir dir;
    if(!dir.exists(backupdir))
    {
        dir.mkdir(backupdir);
        QMessageBox::information(this,"操作备份文件夹创建成功","软件为您创建了操作备份文件夹，每次修改工具中的数据变动都会保存一次完整数据到csv，请自行删除过旧的csv备份文件");
        help->show();
    }
}
bool cmp(USERDATAwithMOD a,USERDATAwithMOD b)
{
    return a.score>b.score;
}
MODmenu::MODmenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MODmenu)
{
    ui->setupUi(this);
    help=new helpmenu;
    help->setWindowIcon(QIcon("myappico.ico"));
    checkfirstrun();
}
MODmenu::~MODmenu()
{
    delete ui;
}
void MODmenu::on_readfile_clicked()
{
    datamodvector.clear();
    achivector.clear();
    //初始化读取数据
    ui->resultlabel->setText("正在读取数据……");
    QFile MOD("../配置文件/成就配置.json");
    QJsonDocument moddoc;
    QJsonArray modarr;
    if(!MOD.open(QIODevice::ReadOnly))
        QMessageBox::critical(this,"critical","读取数据文件错误");
    QByteArray moddata(MOD.readAll());
    MOD.close();
    moddoc=QJsonDocument::fromJson(moddata);
    modarr = moddoc.array();
    QJsonObject achitemp;
    for(int i=0; i<modarr.size(); i++)
    {
        Achievement achisave;
        achitemp=modarr[i].toObject();


        achisave.id=achitemp["id"].toInt();
        if(achisave.id>MaxAchievementID)MaxAchievementID=achisave.id;
        achisave.name=achitemp["名称"].toString();
        QString shortname;
        int flag=0;
        for(int n=0; n<achisave.name.size(); n++)
        {
            if(achisave.name[n]==':')flag=1;
            else if(flag)shortname+=achisave.name[n];
        }
        achisave.name.clear();
        achisave.name=shortname;
        achivector.push_back(achisave);

    }
    numberofachievement=achivector.size();

    QFile file1("../数据/data1.json");	//创建QFile对象，并指定json文件路径
    //打开json文件并判断（不成功则返回0）
    QFile file2("../成就/解锁.json");
    QFile file3("../成就/富甲一方数据.json");
    QJsonDocument jDoc1;
    QJsonDocument jDoc2;
    QJsonDocument jDoc3;
    QJsonArray jArr1;
    QJsonArray jArr2;
    QJsonArray jArr3;
    if(!file1.open(QIODevice::ReadOnly))
        QMessageBox::critical(this,"critical","读取数据文件错误");
    QByteArray data1(file1.readAll());
    file1.close();	//关闭文件
    if(!file2.open(QIODevice::ReadOnly))
        QMessageBox::critical(this,"critical","读取数据文件错误");
    QByteArray data2(file2.readAll());
    file2.close();	//关闭文件
    if(!file3.open(QIODevice::ReadOnly))
        QMessageBox::critical(this,"critical","读取数据文件错误");
    //将文件内容读取到数组中
    QByteArray data3(file3.readAll());
    file3.close();	//关闭文件
    jDoc1 = QJsonDocument::fromJson(data1);
    jDoc2 = QJsonDocument::fromJson(data2);
    jDoc3 = QJsonDocument::fromJson(data3);
    jArr1 = jDoc1.array();
    jArr2 = jDoc2.array();
    jArr3 = jDoc3.array();
    QJsonObject temp1;
    USERDATAwithMOD usertemp;
    for(int i=0; i<jArr1.size(); i++)
    {
        temp1=jArr1[i].toObject();
        usertemp.uid=temp1["UID"].toInt();
        usertemp.name=temp1["名称"].toString();
        usertemp.score=temp1["积分"].toInt();
        usertemp.get=new bool [numberofachievement];
        for(int m=0; m<numberofachievement; m++)usertemp.get[m]=false;

        usertemp.use=0;
        usertemp.level=0;
        datamodvector.push_back(usertemp);
    }
    for(int i=0; i<jArr2.size(); i++)
    {
        temp1=jArr2[i].toObject();
        int uid=temp1["UID"].toInt();
        for(int j=0; j<datamodvector.size(); j++)
        {
            if(uid==datamodvector[j].uid)
            {
                int use=temp1["使用中"].toInt();
                QJsonArray getarray=temp1["已获得"].toArray();
                for(int k=0; k<getarray.size(); k++)
                {
                    int number=getarray[k].toInt();
                    datamodvector[j].get[number-2]=true;

                }
                datamodvector[j].use=use;
                break;
            }
        }
    }
    for(int i=0; i<jArr3.size(); i++)
    {
        temp1=jArr3[i].toObject();
        int uid=temp1["UID"].toInt();
        for(int j=0; j<datamodvector.size(); j++)
        {
            if(uid==datamodvector[j].uid)
            {
                int level=temp1["数据"].toInt();
                datamodvector[j].level=level;
                break;
            }
        }
    }
    qSort(datamodvector.begin(),datamodvector.end(),cmp);
    flashtablefromvector();
    ui->resultlabel->setText("读取数据成功");
    return;
}

void MODmenu::flashtablefromvector()
{
    QStringList headstrList;
    headstrList<<"UID"<<"名称"<<"积分"<<"使用中";
    for(int m=0; m<numberofachievement; m++)
    {
        QString temp=QString::number(achivector[m].id)+achivector[m].name;
        headstrList<<temp;
    }
    headstrList<<"富甲一方等级";

    ui->datatable->setColumnCount(5+numberofachievement);
    ui->datatable->setHorizontalHeaderLabels(headstrList);

    ui->datatable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->datatable->disconnect();
    ui->datatable->setRowCount(datamodvector.size());
    for(int i=0; i<datamodvector.size(); i++)
    {
        QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(datamodvector[i].uid));
        item0->setFlags(Qt::ItemIsEnabled);
        ui->datatable->setItem(i,0,item0);
        QTableWidgetItem *item1 =new QTableWidgetItem(datamodvector[i].name);
        item1->setFlags(Qt::ItemIsEnabled);
        ui->datatable->setItem(i,1,item1);
        ui->datatable->setItem(i,2,new QTableWidgetItem(QString::number(datamodvector[i].score)));
        //V1.1 fix bug
        if(datamodvector[i].use>MaxAchievementID)
        {
            datamodvector[i].use=0;
        }
        if(0==datamodvector[i].use)//
        {
            for(int j=0; j<numberofachievement; j++)
            {
                if(datamodvector[i].get[j])datamodvector[i].use=j+2;
            }
        }
        //V1.1 fix bug

        ui->datatable->setItem(i,3,new QTableWidgetItem(QString::number(datamodvector[i].use)));
        for(int m=0; m<numberofachievement; m++)
        {
            ui->datatable->setItem(i,4+m,new QTableWidgetItem(QString::number(datamodvector[i].get[m])));
        }
        ui->datatable->setItem(i,4+numberofachievement,new QTableWidgetItem(QString::number(datamodvector[i].level)));
    }
    connect(ui->datatable,SIGNAL(cellChanged(int,int)),this,SLOT(on_datatable_cellChanged(int,int)));


    QString datetime=QDateTime::currentDateTime().toString(Qt::ISODate);
    for(int i=0; i<datetime.size(); i++)
    {
        if(datetime[i]==':')
            datetime[i]='-';
    }
    QString backup=backupdir+"/"+datetime+"数据.csv" ;
    QFile output(backup);
    if(!output.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(this,"warning","create backup error");
    }
    QTextStream outcsv(&output);
    outcsv<<"UID"<<','<<QString("名称")<<','<<QString("积分")<<','<<QString("使用中")<<',';
    for(int m=0; m<numberofachievement; m++)
    {
        outcsv<<achivector[m].name<<',';
    }
    outcsv<<QString("富甲一方等级")<<endl;
    for(int i=0; i<datamodvector.size(); i++)
    {
        outcsv<<datamodvector[i].uid<<','<<datamodvector[i].name<<','<<datamodvector[i].score<<','<<datamodvector[i].use<<',';
        for(int m=0; m<numberofachievement; m++)
        {
            outcsv<<datamodvector[i].get[m]<<',';
        }
        outcsv<<datamodvector[i].level<<endl;
    }
    return;
}

void MODmenu::savejson()
{
    ui->resultlabel->setText("正在写入json文件……");
    QJsonArray data1;
    QJsonArray data2;
    QJsonArray data3;
    QFile outfile1("../数据/data1.json");
    QFile outfile2("../成就/解锁.json");
    QFile outfile3("../成就/富甲一方数据.json");
    QJsonObject* temp;
    QJsonDocument *doc;
    QByteArray *json;
    for(int i=0; i<datamodvector.size(); i++)
    {
        temp=new QJsonObject;
        temp->insert("UID",datamodvector[i].uid);
        temp->insert("名称",datamodvector[i].name);
        temp->insert("积分",datamodvector[i].score);
        data1.push_back(*temp);
        delete temp;
    }

    doc=new QJsonDocument(data1);
    json=new QByteArray(doc->toJson());
    outfile1.open(QFile::WriteOnly);
    outfile1.write(*json);
    outfile1.close();
    delete doc;
    delete json;
    QJsonArray *getarray;
    for(int i=0; i<datamodvector.size(); i++)
    {

        if(datamodvector[i].use!=0)
        {
            temp=new QJsonObject;
            temp->insert("UID",datamodvector[i].uid);
            temp->insert("使用中",datamodvector[i].use);
            getarray=new QJsonArray;
            for(int j=0; j<numberofachievement; j++)
            {
                if(datamodvector[i].get[j]==1)getarray->push_back(j+2);
            }
            temp->insert("已获得",*getarray);
            data2.push_back(*temp);
            delete temp;
            delete getarray;
        }

    }
    doc=new QJsonDocument(data2);
    json=new QByteArray(doc->toJson());
    outfile2.open(QFile::WriteOnly);
    outfile2.write(*json);
    outfile2.close();
    delete doc;
    delete json;
    for(int i=0; i<datamodvector.size(); i++)
    {
        if(datamodvector[i].level)
        {
            temp=new QJsonObject;
            temp->insert("UID",datamodvector[i].uid);
            temp->insert("数据",datamodvector[i].level);
            data3.push_back(*temp);
            delete temp;
        }

    }
    doc=new QJsonDocument(data3);
    json=new QByteArray(doc->toJson());
    outfile3.open(QFile::WriteOnly);
    outfile3.write(*json);
    outfile3.close();
    delete doc;
    delete json;
    ui->resultlabel->setText("写入json文件成功");

}
void MODmenu::on_datatable_cellChanged(int row, int column)
{
    if(int(1)==column)
    {
        datamodvector[row].name=ui->datatable->item(row,column)->text();
    }
    else
    {
        QString temp=ui->datatable->item(row,column)->text();
        switch(column)
        {
        case 0 :
            datamodvector[row].uid = temp.toInt();
            break;
        case 2 :
            datamodvector[row].score = temp.toInt();
            break;
        case 3 :
            datamodvector[row].use = temp.toInt();
            break;
        default:
            if(column!=(4+numberofachievement))datamodvector[row].get[column-4]=temp.toInt();
            else datamodvector[row].level=temp.toInt();
            break;
        }
        //V1.1 fix bug
        if(datamodvector[row].use>MaxAchievementID)
        {
            datamodvector[row].use=0;
        }
        //V1.1 fix bug
        if(0==datamodvector[row].use)//0.6版本追加
        {
            for(int i=0; i<numberofachievement; i++)
            {
                if(datamodvector[row].get[i])datamodvector[row].use=i+2;

            }
        }//0.6版本追加

    }
    flashtablefromvector();
    ui->resultlabel->setText(QString("检测到单元格修改，并成功保存数据"));
    return;
}

void MODmenu::on_inputname_textChanged (const QString &arg1)
{
    for(int i=0; i<datamodvector.size(); i++)
    {
        if(arg1==datamodvector[i].name)
        {
            ui->paiming->setText(QString::number(i+1));
            ui->from->setText(QString::number(i+1));
            ui->to->setText(QString::number(i+2));
            return;
        }

    }
    ui->paiming->setText("该用户未找到");
    return;


}
void MODmenu::on_changescoreButton_clicked()
{

    if(!ui->addscore->text().isEmpty())
    {
        if(ui->muladdscore->text().isEmpty())ui->muladdscore->setText(QString::number(1));
        ui->resultlabel->setText(QString("成功批量添加积分")+ui->addscore->text()+"*"+ui->muladdscore->text());
        for(int i=ui->from->text().toInt()-1; i<ui->to->text().toInt()-1; i++)
        {
            datamodvector[i].score+=ui->addscore->text().toInt()*ui->muladdscore->text().toInt();
        }
    }
    else
    {
        ui->resultlabel->setText(QString("成功批量更改积分为")+ui->changescore->text());
        for(int i=ui->from->text().toInt()-1; i<ui->to->text().toInt()-1; i++)
        {
            datamodvector[i].score=ui->changescore->text().toInt();
        }
    }
    flashtablefromvector();
}
void MODmenu::on_pushButton_2_clicked()
{
    std::sort(datamodvector.begin(),datamodvector.end(),cmp);
    flashtablefromvector();
}


void MODmenu::on_addscore_textChanged(const QString &arg1)
{
    ui->changescore->clear();
}


void MODmenu::on_changescore_textChanged(const QString &arg1)
{
    ui->addscore->clear();
}


void MODmenu::on_pushButton_clicked()
{
    for(int i=ui->from->text().toInt()-1; i<ui->to->text().toInt()-1; i++)
    {
        datamodvector[i].get[ui->changeget->text().toInt()-2]=ui->changegetstate->text().toInt();
        if(0==datamodvector[i].use)//0.9版本修复BUG
        {
            for(int m=0; m<numberofachievement; m++)
            {
                if(datamodvector[i].get[m])datamodvector[i].use=m+2;

            }
        }//0.9版本修复BUG
    }

    ui->resultlabel->setText(QString("成功批量操作成就"));

    flashtablefromvector();
}

#define JIETI_0 500000
#define JIETI_1 1000000
#define JIETI_2 5000000
#define JIETI_3 10000000
#define XISHU_0 1//100%
#define XISHU_1 2//50%
#define XISHU_2 4//25%
#define XISHU_3 8//12.5%
int jietijiesuan(int source)
{

    int result=0;
    if(source>JIETI_3)
    {
        result+=(source-JIETI_3)/XISHU_3;
        source=JIETI_3;
    }
    if(source>JIETI_2)
    {
        result+=(source-JIETI_2)/XISHU_2;
        source=JIETI_2;
    }
    if(source>JIETI_1)
    {
        result+=(source-JIETI_1)/XISHU_1;
        source=JIETI_1;
    }
    if(source>JIETI_0)
    {
        result+=(source-JIETI_0)/XISHU_0;
        source=JIETI_0;
    }
    result+=source;
    return result;
}

void MODmenu::on_writefile_clicked()
{
    savejson();
}

void MODmenu::on_calculate_clicked()
{
    for(int i=0; i<datamodvector.size(); i++)
    {
        datamodvector[i].score=jietijiesuan(datamodvector[i].score);
    }
    flashtablefromvector();
}


int MODmenu::uidFindLocation(int uid)
{
    for(int i=0; i<datamodvector.size(); i++)
    {
        if(uid==datamodvector[i].uid)
        {
            return i;
        }
    }
    return -1;
}


void MODmenu::on_inputdataba_clicked()
{
    QString curPath = QDir::currentPath(); //获取系统当前目录
    //获取应用程序的路径
    QString dlgTitle = "请选择本程序生成的带有UID的数据文件"; //对话框标题
    QString filter = "本程序生成的原始数据文件(*.csv)"; //文件过滤器
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    QTextCodec *codec = QTextCodec::codecForName("GBK");

    QFile otherdatabase(aFileName);

    if(!otherdatabase.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        ui->resultlabel->setText("open other database error");
        return;
    }
    QByteArray line = otherdatabase.readLine();
    QString temp;
    temp=codec->toUnicode(line);


    //QTextStream input(&otherdatabase);
    //QString temp = input.readLine();
    int j=0;
    QString *part=new QString [5+numberofachievement];
    while(!otherdatabase.atEnd())
    {
        line.clear();
        temp.clear();
        //temp = input.readLine();
        line = otherdatabase.readLine();
        temp=codec->toUnicode(line);

        j=0;
        for(int i=0; i<5+numberofachievement; i++)
        {
            part[i].clear();
        }

        for(int i=0; i<temp.size(); i++)
        {


            if(temp[i]==',')j++;
            else
            {
                part[j]+=temp[i];
            }

        }

        int local=uidFindLocation(part[0].toInt());

        if(local<0)
        {
            USERDATAwithMOD newuser;
            newuser.uid=part[0].toInt();
            newuser.name=part[1];
            newuser.score=part[2].toInt();
            newuser.use=part[3].toInt();
            int m=0,n=4;
            for(m=0,n=4; m<numberofachievement; m++,n++)
            {
                newuser.get[m]=part[n].toInt();
            }
            newuser.level=part[n].toInt();
            datamodvector.push_back(newuser);
        }
        else
        {
            datamodvector[local].score+=part[2].toInt();
        }
    }
    flashtablefromvector();
    return;
}

void MODmenu::on_help_clicked()
{
    help->show();
}



