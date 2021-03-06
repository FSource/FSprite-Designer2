#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>

#include "widget/SdResourceExploreWidget.h"

SdResourceExploreWidget::SdResourceExploreWidget()
{
    init();
    layout();
	slotCurProjectChange();
}
SdResourceExploreWidget::~SdResourceExploreWidget()
{
	destroy();
}

void SdResourceExploreWidget::setNameFilters(const QStringList& list)
{
    m_fileModel->setNameFilters(list);
}

void SdResourceExploreWidget::slotCurProjectChange()
{
	QModelIndex root=m_fileModel->setRootPath("E:/");
	m_resourceView->setModel(m_fileModel);
	m_resourceView->setRootIndex(root);
	m_resourceView->setColumnHidden(1,true);
	m_resourceView->setColumnHidden(2,true);
	m_resourceView->setColumnHidden(3,true);
}
void SdResourceExploreWidget::slotFileSelect(const QModelIndex& index)
{
	QFileInfo file_info=m_fileModel->fileInfo(index);
	if(file_info.isDir())
	{
		return ;
	}

	/*
	QString file_name=file_info.filePath();
	QString file_relative_name=MdUtil::toProjectPath(file_name);
	emit signalFileSelect(file_relative_name);

	FS_TRACE_WARN("file_name=%s",file_relative_name.toStdString().c_str());
	*/
}

void SdResourceExploreWidget::init()
{
	m_fileModel=new QFileSystemModel();
	m_fileModel->setReadOnly(true);
	m_fileModel->setFilter(QDir::AllDirs|QDir::Files|QDir::NoSymLinks|QDir::NoDotAndDotDot );
	m_fileModel->setNameFilterDisables(false);

	m_resourceView=new QTreeView(this);
	m_resourceView->setHeaderHidden(true);

	/*
	connect(MdData::shareData(),SIGNAL(signalCurProjectChange()),this,SLOT(slotCurProjectChange()));
	connect(m_resourceView,SIGNAL(clicked(const QModelIndex&)),this,SLOT(slotFileSelect(const QModelIndex&)));
	*/
}
void SdResourceExploreWidget::layout()
{
	QVBoxLayout* vlayout=new QVBoxLayout;
	vlayout->addWidget(m_resourceView);
	vlayout->setSpacing(0);
	vlayout->setContentsMargins(0,0,0,0);
	setLayout(vlayout);
}

void SdResourceExploreWidget::destroy()
{
	delete m_fileModel;
	delete m_resourceView;
}


