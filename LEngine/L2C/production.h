#ifndef __PRODUCTION_H__
#define __PRODUCTION_H__

enum ProductionType
{
  eProduction,
  eDecomposition,
  eInterpretation
};

class FormalModuleDtList;


class ProductionProto
{
public:
	ProductionProto(FormalModuleDtList*, FormalModuleDtList*, FormalModuleDtList*);
	~ProductionProto();
	void Generate() const;
	void GenerateCaller() const;
	void GenerateProtoEntry() const;
	FormalModuleDtList* GetStrct()const{return _pStrct;}
	FormalModuleDtList* GetLeftContext()const{return _pLCntxt;}
	FormalModuleDtList* GetRightContext()const{return _pRCntxt;}
private:
	FormalModuleDtList* _pLCntxt;
	FormalModuleDtList* _pStrct;
	FormalModuleDtList* _pRCntxt;
	int _id;
	ProductionType _type;
	static int _counter;
};

typedef ProductionProto* pProductionProto;

class ProductionTable
{
public:
	ProductionTable();
	~ProductionTable();
	void Add(ProductionProto*);
	int Items() const
	{ return _items; }
	const ProductionProto* GetProto(int i) const
	{
		assert(i>=0);
		assert(i<_items);
		return _arr[i];
	}
private:
	void _Grow();
	enum
	{ eInitSize = 64 };
	pProductionProto* _arr;
	int _items;
	int _size;
};


class ProductionTableIterator
{
public:
	ProductionTableIterator(const ProductionTable& tbl) : _tbl(tbl)
	{
		_current = 0;
	}
	void operator++(int)
	{
		assert(!AtEnd());
		_current++;
	}
	bool AtEnd() const
	{
		assert(_current<=_tbl.Items());
		return _tbl.Items() == _current;
	}
	const ProductionProto* GetCurrent() const
	{
		assert(!AtEnd());
		return _tbl.GetProto(_current);
	}
	int CurrentPosition() const{
	  return _current;
	}
	void Reset(){
	  _current = 0;
	}
private:
	const ProductionTable& _tbl;
	int _current;
};


#else
	#error File already included
#endif
