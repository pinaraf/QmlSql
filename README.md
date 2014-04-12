QmlSql
======

Sql plugin for QtQuick 2 (Qt5)

The aim with this project is to allow very fast development of data-driven application.

Binding fields from your form to your SQL query is painless, using notifications from PostgreSQL or Firebird, your QtQuick application can refresh instantly as soon as data changes in the database…

This is still alpha-state software, released in the hope people will be interested in it and suggest improvements.


Example
=======

    SqlQueryModel {
        id: baseSqlQuery
        query: "SELECT id, name FROM main_items;"
        refreshNotification: "changes_main_items"
    }

    SqlQueryModel {
        id: subSqlQuery
        query: "SELECT id, name FROM sub_items WHERE main = :main;"
        bindings: [
            SqlQueryBinding {
                name: ":main"
                value: baseSqlQuery.getValue(mainComboBox.currentIndex, "id")
            }
        ]
        refreshNotification: "changes_sub_items"
    }

    ComboBox {
        id: mainComboBox
        height: 23
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: button1.left
        anchors.rightMargin: 6
        model: baseSqlQuery
        textRole: "name"
    }

    TableView {
        id: tableView1
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        model: subSqlQuery
        anchors.top: mainComboBox.bottom

        TableViewColumn {
            role: "id"
            title: "Id"
        }

        TableViewColumn {
            role: "name"
            title: "name"
        }
    }
