#ifndef BOX_H
#define BOX_H
#include "item.h"
#include "jsonmanager.h"
#include <QVector>
class Box: public JsonManager{
friend class ItemIterator;
private:
    static QJsonArray storage;
    static QString path;
	class ItemNode{
	friend class Box;
	private:
		Item* item;
		ItemNode* next;
	public:
		ItemNode();
		ItemNode(const ItemNode&);
		ItemNode(Item*);
		ItemNode& operator=(const ItemNode&);
		ItemNode& operator=(const Item&);
		bool operator==(const ItemNode&)const;
		bool operator!=(const ItemNode&)const;
		Item* getItem();
		ItemNode* getNext();
	};
public:
	enum Color{Red, Blue, Green, Yellow, Orange, Purple};
	enum Type{Closed, Amoeba, Danish, Sewing, Quisquilia};
	static const unsigned int MAX_CAPACITY;
	static const unsigned int MIN_CAPACITY;
    QString filename() const;
    QJsonArray* getStorage() const;
protected:
	static ItemNode* deepCopy(ItemNode*);
	static void deepDestruction(ItemNode*);
	Color color;
    QString code;
	unsigned int capacity;
	unsigned int size;
	bool opened;
	ItemNode* firstItem;
public:
    Box(Color = Red, QString = "", unsigned int = MIN_CAPACITY, unsigned int = 0, int = -1);
	Box(const Box&);
	Box& operator=(const Box&);
	~Box();
    QString getCode() const;
	unsigned int getSize() const;
	unsigned int getCapacity() const;
	Color getColor() const;
    QString cssColor() const;
	void setOpened(bool o = true);
	bool empty() const;
	bool full() const;
    static Item* jsonItem(QJsonObject item);
	void recoveItems();
    void updateItems();
    static Box* fromJson(QJsonObject);
    QJsonObject toJson() const override;
    bool checkUniq() const override;
    static QVector<Box*> getAll();
    static bool saveAll();

	Item* itemAt(int);
	virtual bool pushItem(Item*);
	virtual Item* popItem();
    Item* popByCode(QString code);
	virtual Type type() const;
    virtual QString itemHeader() const;
    static QString header();
    QString infoLine() const;


	class ItemIterator{
	friend class Box;
	private:
		Box::ItemNode* node;
	public:
		Item* item();
		ItemIterator operator++(int);
		ItemIterator& operator++();
		bool operator==(const ItemIterator&)const;
		bool operator!=(const ItemIterator&)const;
	};
	ItemIterator begin() const;
	ItemIterator end() const;
	int countItem() const;

    class CapacityOverhead{};
    class SizeOverhead{};
    class BoxClosed{};
    class BoxFull{};
};
#endif
