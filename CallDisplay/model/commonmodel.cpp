#include "commonmodel.h"
#include <QDebug>

CommonModel::CommonModel(QHash<int, QByteArray> &names, QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames = names;
    m_items = new QList<CommonModelItem>();
    m_itemAdds = new QList<CommonModelItem>();
    connect(this, SIGNAL(update()),
            this, SLOT(onUpdate()));
}

CommonModel::~CommonModel()
{
    delete m_items;
    delete m_itemAdds;
}

// 返回列数
int CommonModel::rowCount(const QModelIndex &parent) const
{
    return m_items->count();
}

// 返回行数
QVariant CommonModel::data(const QModelIndex &index, int role) const
{
    const CommonModelItem& item = m_items->at(index.row());
    int ind = role - RoleColumn0;

    if(ind < 0 || ind >= item.columns.count())
    {
        return QVariant();
    }

    return item.columns.at(ind);
}

// 返回列名
QHash<int, QByteArray> CommonModel::roleNames() const
{
    return m_roleNames;
}

// 清除所有数据
void CommonModel::BeginAdd()
{
    m_itemAdds->clear();
}

// 添加数据
void CommonModel::Add(CommonModelItem item)
{
    m_itemAdds->push_back(item);
}

// 更新通知
void CommonModel::EndAdd()
{
    emit update();
}

// 执行更新
void CommonModel::onUpdate()
{
    beginResetModel();
    // 交互两个队列
    QList<CommonModelItem> *tmp;
    tmp = m_items;
    m_items = m_itemAdds;
    m_itemAdds = m_items;
    // 完成更新
    endResetModel();
    qDebug() << "CommonModel::onUpdate";
}
