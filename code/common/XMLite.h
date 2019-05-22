// XMLite.h: interface for the XMLite class.
//
// XMLite : XML Lite Parser Library
// by bro ( Cho,Kyung Min: bro@shinbiro.com ) 2002-10-30
// Microsoft MVP (Visual C++) bro@msmvp.com
// 
// History.
// 2002-10-29 : First Coded. Parsing XMLElelement and Attributes.
//              get xml parsed string ( looks good )
// 2002-10-30 : Get Node Functions, error handling ( not completed )
// 2002-12-06 : Helper Funtion string to long
// 2002-12-12 : Entity Helper Support
// 2003-04-08 : Close, 
// 2003-07-23 : add property escape_value. (now no escape on default)
// 2003-10-24 : bugfix) attribute parsing <tag a='1' \r\n/> is now ok
// 2004-03-05 : add branch copy functions
// 2004-06-14 : add _tcseistr/_tcsenistr/_tcsenicmp functions
// 2004-06-14 : now support, XML Document and PI, Comment, CDATA node
// 2004-06-15 : add GetText()/ Find() functions
// 2004-06-15 : add force_parse : now can parse HTML (not-welformed xml)
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLITE_H__786258A5_8360_4AE4_BDAF_2A52F8E1B877__INCLUDED_)
#define AFX_XMLITE_H__786258A5_8360_4AE4_BDAF_2A52F8E1B877__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <deque>
#include <string>
#pragma warning(disable:4996)
// #ifndef WIN32
// typedef char *LPTSTR;
// typedef const char *LPCTSTR;
// #endif


struct _tagXMLAttr;
typedef _tagXMLAttr XAttr, *LPXAttr;
typedef std::vector<LPXAttr> XAttrs;

//class _tagXMLNode;
//typedef _tagXMLNode XNode, *LPXNode;
//typedef std::vector<LPXNode> XNodes, *LPXNodes;
class XNode;
typedef XNode *LPXNode;
typedef std::vector<LPXNode> XNodes, *LPXNodes;

class _tagXMLDocument;
typedef class _tagXMLDocument XDoc, *LPXDoc;

// Entity Encode/Decode Support
typedef class _tagXmlEntity
{
public:
	char entity;					// entity ( & " ' < > )
	char ref[10];					// entity reference ( &amp; &quot; etc )
	int ref_len;					// entity reference length
}XENTITY,*LPXENTITY;

typedef class _tagXMLEntitys : public std::vector<XENTITY>
{
public:
	LPXENTITY GetEntity( int entity );
	LPXENTITY GetEntity( char* entity );	
	int GetEntityCount( const char* str );
	int Ref2Entity( const char* estr, char* str, int strlen );
	int Entity2Ref( const char* str, char* estr, int estrlen );
	std::string Ref2Entity( const char* estr );
	std::string Entity2Ref( const char* str );	

	_tagXMLEntitys(){};
	_tagXMLEntitys( LPXENTITY entities, int count );
}XENTITYS, *LPXENTITYS;
extern XENTITYS entityDefault;
std::string  XRef2Entity( const char* estr );
std::string  XEntity2Ref( const char* str );	

typedef enum 
{
	PIE_PARSE_WELFORMED	= 0,
	PIE_ALONE_NOT_CLOSED,
	PIE_NOT_CLOSED,
	PIE_NOT_NESTED,
	PIE_ATTR_NO_VALUE
}PCODE;

// Parse info.
typedef class _tagParseInfo
{
public:
	bool		trim_value;			// [set] do trim when parse?
	bool		entity_value;		// [set] do convert from reference to entity? ( &lt; -> < )
	LPXENTITYS	entitys;			// [set] entity table for entity decode
	char		escape_value;		// [set] escape value (default '\\')
	bool		force_parse;		// [set] force parse even if xml is not welformed

	char*		xml;				// [get] xml source
	bool		erorr_occur;		// [get] is occurance of error?
	char*		error_pointer;		// [get] error position of xml source
	PCODE		error_code;			// [get] error code
	std::string		error_string;		// [get] error string

	LPXDoc		doc;
	_tagParseInfo() { trim_value = false; entity_value = true; force_parse = false; entitys = &entityDefault; xml = NULL; erorr_occur = false; error_pointer = NULL; error_code = PIE_PARSE_WELFORMED; escape_value = '\\'; doc = NULL; }
}PARSEINFO,*LPPARSEINFO;
extern PARSEINFO piDefault;

// display optional environment
 typedef class _tagDispOption
{
public:
	bool newline;			// newline when new tag
	bool reference_value;	// do convert from entity to reference ( < -> &lt; )
	char value_quotation_mark;	// val="" (default value quotation mark "
	LPXENTITYS	entitys;	// entity table for entity encode

	int tab_base;			// internal usage
	_tagDispOption() { newline = true; reference_value = true; entitys = &entityDefault; tab_base = 0; value_quotation_mark = '"'; }
}DISP_OPT, *LPDISP_OPT;
extern DISP_OPT optDefault;

// XAttr : Attribute Implementation
typedef struct _tagXMLAttr
{
public:
	std::string name;
	std::string	value;
	
	XNode*	parent;

	std::string GetXML( LPDISP_OPT opt = &optDefault );
}XAttr, *LPXAttr;

typedef enum
{
	XNODE_ELEMENT,				// general node '<element>...</element>' or <element/>
	XNODE_PI,					// <?xml version="1.0" ?>
	XNODE_COMMENT,				// <!-- comment -->
	XNODE_CDATA,				// <![CDATA[ cdata ]]>
	XNODE_DOC,					// internal virtual root
}NODE_TYPE;

// XMLNode structure
//typedef class _tagXMLNode
class XNode
{
public:
	// name and value
	std::string name;
	std::string	value;

	// internal variables
	LPXNode	parent;		// parent node
	XNodes	childs;		// child node
	XAttrs	attrs;		// attributes
	NODE_TYPE type;		// node type 
	LPXDoc	doc;		// document

	// Load/Save XML
	char*	Load( const char* pszXml, LPPARSEINFO pi = &piDefault );
	std::string GetXML( LPDISP_OPT opt = &optDefault );
	std::string GetText( LPDISP_OPT opt = &optDefault );

	// internal load functions
	char*	LoadAttributes( const char* pszAttrs, LPPARSEINFO pi = &piDefault );
	char*	LoadAttributes( const char* pszAttrs, const char* pszEnd, LPPARSEINFO pi = &piDefault );
	char*	LoadProcessingInstrunction( const char* pszXml, LPPARSEINFO pi = &piDefault );
	char*	LoadComment( const char* pszXml, LPPARSEINFO pi = &piDefault ); 
	char*	LoadCDATA( const char* pszXml, LPPARSEINFO pi = &piDefault ); 

	// in own attribute list
	LPXAttr	GetAttr( const char* attrname ); 
	const char*	GetAttrValue( const char* attrname ); 
	XAttrs	GetAttrs( const char* name ); 

	// in one level child nodes
	LPXNode	GetChild( const char* name ); 
	const char*	GetChildValue( const char* name ); 
	std::string	GetChildText( const char* name, LPDISP_OPT opt = &optDefault );
	XNodes	GetChilds( const char* name ); 
	XNodes	GetChilds(); 

	LPXAttr GetChildAttr( const char* name, const char* attrname );
	const char* GetChildAttrValue( const char* name, const char* attrname );
	
	// search node
	LPXNode	Find( const char* name );

	// modify DOM 
	int		GetChildCount();
	LPXNode GetChild( int i );
	XNodes::iterator GetChildIterator( LPXNode node );
	LPXNode CreateNode( const char* name = NULL, const char* value = NULL );
	LPXNode	AppendChild( const char* name = NULL, const char* value = NULL );
	LPXNode	AppendChild( LPXNode node );
	bool	RemoveChild( LPXNode node );
	LPXNode DetachChild( LPXNode node );

	// node/branch copy
	void	CopyNode( LPXNode node );
	void	CopyBranch( LPXNode branch );
	void	_CopyBranch( LPXNode node );
	LPXNode	AppendChildBranch( LPXNode node );

	// modify attribute
    int     GetAttrCount();
	LPXAttr GetAttr( int i );
	XAttrs::iterator GetAttrIterator( LPXAttr node );
	LPXAttr CreateAttr( const char* anem = NULL, const char* value = NULL );
	LPXAttr AppendAttr( const char* name = NULL, const char* value = NULL );
	LPXAttr	AppendAttr( LPXAttr attr );
	bool	RemoveAttr( LPXAttr attr );
	LPXAttr DetachAttr( LPXAttr attr );

	// operator overloads
	LPXNode operator [] ( int i ) { return GetChild(i); }
	XNode& operator = ( XNode& node ) { CopyBranch(&node); return *this; }

	XNode() { parent = NULL; doc = NULL; type = XNODE_ELEMENT; }
	~XNode();

	void Close();

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//unicode modify by lsj 2008.1.24
/*public:
	std::wstring	Load( const wchar_t* pszXml, LPPARSEINFO pi = &piDefault )
	{
		std::string _pszXml=CUtilString::WString2String(pszXml);
		std::string strTemp=Load(_pszXml.c_str(),pi);
		return CUtilString::String2WString(strTemp.c_str());
	}
	std::wstring GetXML_W( LPDISP_OPT opt = &optDefault )
	{
		std::string str=GetXML(opt);
		return CUtilString::String2WString(str.c_str());
	}
	std::wstring GetText_W( LPDISP_OPT opt = &optDefault )
	{
		std::string str=GetText(opt);
		return CUtilString::String2WString(str.c_str());
	}
	LPXAttr	GetAttr( const wchar_t* attrname )
	{
		std::string str=CUtilString::WString2String(attrname);
		return GetAttr(str.c_str());
	}
	std::wstring	GetAttrValue( const wchar_t* attrname )
	{
		std::string _attrname=CUtilString::WString2String(attrname);
		std::string strTemp=GetAttrValue(_attrname.c_str());
		return CUtilString::String2WString(strTemp.c_str());
	}
	XAttrs	GetAttrs( const wchar_t* name )
	{
		std::string str=CUtilString::WString2String(name);
		return GetAttrs(str.c_str());
	}
	LPXNode	GetChild( const wchar_t* name )
	{
		std::string str=CUtilString::WString2String(name);
		return GetChild(str.c_str());
	}
	std::wstring	GetChildValue( const wchar_t* name )
	{
		std::string _name=CUtilString::WString2String(name);
		std::string strTemp=GetChildValue(_name.c_str());
		return CUtilString::String2WString(strTemp.c_str());
	}
	std::wstring  GetChildText( const wchar_t* name, LPDISP_OPT opt = &optDefault )
	{
		std::string _name=CUtilString::WString2String(name);
		std::string sResult=GetChildText(_name.c_str(),opt);
		return CUtilString::String2WString(sResult.c_str());
	}
	XNodes	GetChilds( const wchar_t* name )
	{
		std::string str=CUtilString::WString2String(name);
		return GetChilds(str.c_str());
	}
	LPXAttr GetChildAttr( const wchar_t* name, const wchar_t* attrname )
	{
		std::string _name=CUtilString::WString2String(name);
		std::string _attrname=CUtilString::WString2String(attrname);
		return GetChildAttr(_name.c_str(),_attrname.c_str());
	}
	std::wstring GetChildAttrValue( const wchar_t* name, const wchar_t* attrname )
	{
		std::string _name=CUtilString::WString2String(name);
		std::string _attrname=CUtilString::WString2String(attrname);
		std::string strTemp=GetChildAttrValue(_name.c_str(),_attrname.c_str());
		return CUtilString::String2WString(strTemp.c_str());
	}
	LPXNode	Find( const wchar_t* name )
	{
		std::string _name=CUtilString::WString2String(name);
		return Find(_name.c_str());
	}
	LPXNode CreateNode( const wchar_t* name = NULL, const wchar_t* value = NULL )
	{
		std::string _name=CUtilString::WString2String(name);
		std::string _value=CUtilString::WString2String(value);
		return CreateNode(_name.c_str(),_value.c_str());
	}
	LPXNode	AppendChild( const wchar_t* name = NULL, const wchar_t* value = NULL )
	{
		std::string _name=CUtilString::WString2String(name);
		std::string _value=CUtilString::WString2String(value);
		return AppendChild(_name.c_str(),_value.c_str());
	}
	LPXAttr CreateAttr( const wchar_t* anem = NULL, const wchar_t* value = NULL )
	{
		std::string _anem=CUtilString::WString2String(anem);
		std::string _value=CUtilString::WString2String(value);
		return CreateAttr(_anem.c_str(),_value.c_str());
	}
	LPXAttr AppendAttr( const wchar_t* name = NULL, const wchar_t* value = NULL )
	{
		std::string _name=CUtilString::WString2String(name);
		std::string _value=CUtilString::WString2String(value);
		return AppendAttr(_name.c_str(),_value.c_str());
	}*/
	/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
};//XNode, *LPXNode;

// XMLDocument structure
typedef class _tagXMLDocument : public XNode
{
public:
	PARSEINFO	parse_info;

	_tagXMLDocument() { parent = NULL; doc = this; type = XNODE_DOC; }
	
	char*	Load( const char* pszXml, LPPARSEINFO pi = NULL );
	LPXNode	GetRoot();

}XDoc, *LPXDoc;

// Helper Funtion
inline long XStr2Int( const char* str, long default_value = 0 )
{
	return ( str && *str ) ? atol(str) : default_value;
}

bool XIsEmptyString( const char* str );
/*
inline bool XIsEmptyString( const char* str )
{
	std::string s;
	s = str;
	TrimLeft(s);
	TrimRight(s);
	
	//return ( s.empty() || s == _T("") );
	return ( s.empty() || (0== strcmp(s.c_str(), "" ) ));
}
*/

#endif // !defined(AFX_XMLITE_H__786258A5_8360_4AE4_BDAF_2A52F8E1B877__INCLUDED_)
