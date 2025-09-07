#include "Delegate.h"
#include <QFont>
#include <QBrush>
#include "TableMode.h"
#include <QPixmap>
#include <QPainter>

PictureDelegate::PictureDelegate(QWidget* parent) : QStyledItemDelegate{ parent } {

}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    QString coat = index.model()->data(index, Qt::EditRole).toString();

    if (index.column() != 1) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    if (coat.contains("Blue")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\5120x2880-dark-blue-solid-color-background.jpg)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("Pink")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\Rose-pink.jpg)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("Red")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\Red_Color.jpg)");
        painter->drawPixmap(option.rect, pixMap);
    
    }
    else if (coat.contains("Orange")) {
        QPixmap pixMap("orange.jpg");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("Green")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\green.jpg)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("Grey")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\gray.jpg)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("Black")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\black.jpg)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("White")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\descărcare.png)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("Brown")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\sdad.png)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else if (coat.contains("Purple")) {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\pruple.png)");
        painter->drawPixmap(option.rect, pixMap);
    }
    else
    {
        QPixmap pixMap(R"(D:\desktop2\oop\lab10\lab10\jhg.jpg)");
        painter->drawPixmap(option.rect, pixMap);
    }
}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    if (index.column() == 1) {
        return QSize(300, 300);
    }
    return QStyledItemDelegate::sizeHint(option, index);
}