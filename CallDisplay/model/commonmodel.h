#ifndef COMMONMODEL_H
#define COMMONMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QVector>
#include <QMutex>

class CommonModelItem
{
public:
    CommonModelItem()
    {

    }

    // 一个参数
    CommonModelItem(QString col0)
    {
        columns.push_back(col0);
    }

    // 两个参数
    CommonModelItem(QString col0, QString col1)
    {
        columns.push_back(col0);
        columns.push_back(col1);
    }

    // 三个参数
    CommonModelItem(QString col0, QString col1, QString col2)
    {
        columns.push_back(col0);
        columns.push_back(col1);
        columns.push_back(col2);
    }

    // 四个参数
    CommonModelItem(QString col0, QString col1, QString col2,
                    QString col3)
    {
        columns.push_back(col0);
        columns.push_back(col1);
        columns.push_back(col2);
        columns.push_back(col3);
    }

    // 五个参数
    CommonModelItem(QString col0, QString col1, QString col2,
                    QString col3, QString col4)
    {
        columns.push_back(col0);
        columns.push_back(col1);
        columns.push_back(col2);
        columns.push_back(col3);
        columns.push_back(col4);
    }

    CommonModelItem(const CommonModelItem& item)
    {
        columns = item.columns;
    }

public:
    QVector<QString>    columns;
};



class CommonModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum CommonRoles {
        RoleColumn0 = Qt::UserRole + 1,
        RoleColumn1,
        RoleColumn2,
        RoleColumn3,
        RoleColumn4,
        RoleColumn5
    };

public:
    explicit CommonModel(QHash<int, QByteArray>& names, QObject *parent = 0);
    ~CommonModel();

signals:
    void update();

public slots:
    void onUpdate();

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;


public:
    void    BeginAdd();
    void    Add(CommonModelItem item);
    void    EndAdd();

private:
    QList<CommonModelItem>     *m_items;
    QList<CommonModelItem>     *m_itemAdds;
    QHash<int, QByteArray>      m_roleNames;
};

#endif // COMMONMODEL_H
