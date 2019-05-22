// XMLite.cpp: implementation of the XMLite class.
//
//////////////////////////////////////////////////////////////////////
#include "XMLite.h"
#include <iostream>
#include <sstream>
#include <string>
#include "utility.h"

PARSEINFO piDefault;
DISP_OPT optDefault; 
static const char chXMLTagOpen = '<';
static const char chXMLTagClose = '>';
static const char chXMLTagPre = '/';
static const char chXMLEscape = '\\';	// for value field escape

static const char szXMLPIOpen[] = "<?";
static const char szXMLPIClose[] = "?>";
static const char szXMLCommentOpen[] = "<!--";
static const char szXMLCommentClose[] = "-->";
static const char szXMLCDATAOpen[] = "<![CDATA[";
static const char szXMLCDATAClose[] = "]]>";

static const XENTITY x_EntityTable[] =
{
	{ '&', "&amp;", 5 }, { '\"', "&quot;", 6 }, { '\'', "&apos;", 6 },
	{ '<', "&lt;", 4 }, { '>', "&gt;", 4 }
};

//PARSEINFO piDefault;
//DISP_OPT optDefault;
XENTITYS entityDefault((LPXENTITY)x_EntityTable,
	sizeof(x_EntityTable) / sizeof(x_EntityTable[0]));
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//========================================================
// Name   : _tcschrs
// Desc   : same with _tcspbrk 
// Param  :
// Return :
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* _tcschrs(const char* psz, const char* pszchs)
{
	while (psz && *psz)
	{
		if (strchr(pszchs, *psz))
			return (char *) psz;
		psz++;
	}
	return NULL;
}

//========================================================
// Name   : _tcsskip
// Desc   : skip space
// Param  : 
// Return : skiped string
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* _tcsskip(const char* psz)
{
	//while( psz && *psz == ' ' && *psz == 13 && *psz == 10 ) psz++;
	while (psz && isspace(*psz))
		psz++;

	return (char *) psz;
}

//========================================================
// Name   : _tcsechr
// Desc   : similar with _tcschr with escape process
// Param  : escape - will be escape character
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* _tcsechr(const char* psz, int ch, int escape)
{
	char* pch = (char*) psz;

	while (pch && *pch)
	{
		if (escape != 0 && *pch == escape)
			pch++;
		else if (*pch == ch)
			return (char *) pch;
		pch++;
	}
	return pch;
}

//========================================================
// Name   : _tcselen
// Desc   : similar with _tcslen with escape process
// Param  : escape - will be escape character
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
int _tcselen(int escape, char* srt, char* end = NULL)
{
	int len = 0;
	char* pch = srt;
	if (end == NULL)
		end = (char *)sizeof(long);
	char* prev_escape = NULL;
	while (pch && *pch && pch < end)
	{
		if (escape != 0 && *pch == escape && prev_escape == NULL)
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			len++;
		}
		pch++;
	}
	return len;
}

//========================================================
// Name   : _tcsecpy
// Desc   : similar with _tcscpy with escape process
// Param  : escape - will be escape character
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
void _tcsecpy(char* psz, int escape, char* srt, char* end = NULL)
{
	char* pch = srt;
	if (end == NULL)
		end = (char *)sizeof(long);
	char* prev_escape = NULL;
	while (pch && *pch && pch < end)
	{
		if (escape != 0 && *pch == escape && prev_escape == NULL)
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			*psz++ = *pch;
		}

		pch++;
	}

	*psz = '\0';
}

//========================================================
// Name   : _tcsepbrk
// Desc   : similar with _tcspbrk with escape process
// Param  : escape - will be escape character
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* _tcsepbrk(const char* psz, const char* chset, int escape)
{
	char* pch = (char*) psz;
	char* prev_escape = NULL;
	while (pch && *pch)
	{
		if (escape != 0 && *pch == escape && prev_escape == NULL)
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			//if( _tcschr( chset, *pch ) )
			if (strchr(chset, *pch))
				return (char *) pch;
		}
		pch++;
	}
	return pch;
}

//========================================================
// Name   : _tcsenicmp
// Desc   : similar with _tcsnicmp with escape process
// Param  : escape - will be escape character
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
int _tcsenicmp(const char* psz, const char* str, int len, int escape)
{
	char* pch = (char*) psz;
	char* prev_escape = NULL;
	char* des = (char*) str;
	int i = 0;

	while (pch && *pch && i < len)
	{
		if (escape != 0 && *pch == escape && prev_escape == NULL)
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			if (tolower(*pch) != tolower(des[i]))
				break;
			i++;
		}
		pch ++;
	}

	// find
	if (i == len)
		return 0;
	if (psz[i] > des[i])
		return 1;
	return -1;
}

//========================================================
// Name   : _tcsenistr
// Desc   : similar with _tcsistr with escape process
// Param  : escape - will be escape character
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* _tcsenistr(const char* psz, const char* str, int len, int escape)
{
	char* pch = (char*) psz;
	char* prev_escape = NULL;
	char* des = (char*) str;
	int i = 0;

	while (pch && *pch)
	{
		if (escape != 0 && *pch == escape && prev_escape == NULL)
			prev_escape = pch;
		else
		{
			prev_escape = NULL;
			if (_tcsenicmp(pch, str, len, escape) == 0)
				return (char *) pch;
		}
		pch++;
	}
	return pch;
}

//========================================================
// Name   : _tcseistr
// Desc   : similar with _tcsistr with escape process
// Param  : escape - will be escape character
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* _tcseistr(const char* psz, const char* str, int escape)
{
	int len = strlen(str);
	return _tcsenistr(psz, str, len, escape);
}

//========================================================
// Name   : _SetString
// Desc   : put string of (psz~end) on ps string
// Param  : trim - will be trim?
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
/*
void _SetString( char* psz, char* end, CString* ps, bool trim = FALSE, int escape = 0 )
{
	//trim
	if( trim )
	{
		while( psz && psz < end && _istspace(*psz) ) psz++;
		while( (end-1) && psz < (end-1) && _istspace(*(end-1)) ) end--;
	}
	int len = end - psz;
	if( len <= 0 ) return;
	if( escape )
	{
		len = _tcselen( escape, psz, end );
		char* pss = ps->GetBufferSetLength( len );
		_tcsecpy( pss, escape, psz, end );
	}
	else
	{
		char* pss = ps->GetBufferSetLength(len + 1 );
		memcpy( pss, psz, len );
		pss[len] = '\0';
	}
}
*/
void _SetString(char* psz, char* end, std::string& ps, bool trim = false,
	int escape = 0)
{
	//trim
	if (trim)
	{
		while (psz && psz < end && isspace(*psz))
			psz++;
		while ((end - 1) && psz < (end - 1) && isspace(*(end - 1)))
			end--;
	}
	int len = end - psz;
	if (len <= 0)
		return;
	if (escape)
	{
		len = _tcselen(escape, psz, end);
		//char* pss = ps->GetBufferSetLength( len );
		ps.resize(len);
		char* pss = const_cast<char*>(ps.c_str());
		_tcsecpy(pss, escape, psz, end);
	}
	else
	{
	    char* pTemp = NULL;
        pTemp = new char[len+1];
       // assert(NULL != pTemp);
        if (NULL != pTemp)
        {
            memcpy( pTemp, psz, len );
		    pTemp[len] = '\0';
            ps = pTemp;
            delete []pTemp;
        }
        else
        {
            ps = "";
        }
	}
}

XNode::~XNode()
{
	Close();
}

void XNode::Close()
{
	unsigned int i;
	for (i = 0 ; i < childs.size(); i ++)
	{
		LPXNode p = childs[i];
		if (p)
		{
			delete p; childs[i] = NULL;
		}
	}
	childs.clear();

	for (i = 0 ; i < attrs.size(); i ++)
	{
		LPXAttr p = attrs[i];
		if (p)
		{
			delete p; attrs[i] = NULL;
		}
	}
	attrs.clear();
}

// attr1="value1" attr2='value2' attr3=value3 />
//  										  ^- return pointer
//========================================================
// Name   : LoadAttributes
// Desc   : loading attribute plain xml text
// Param  : pszAttrs - xml of attributes
//  		pi = parser information
// Return : advanced string pointer. (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* XNode::LoadAttributes(const char* pszAttrs,
	LPPARSEINFO pi /*= &piDefault*/)
{
	char* xml = (char*) pszAttrs;

	while (xml && *xml)
	{
		if (xml = _tcsskip(xml))
		{
			// close tag
			if (*xml == chXMLTagClose || *xml == chXMLTagPre)
				// wel-formed tag
				return xml;

			// XML Attr Name
			char* pEnd = strpbrk(xml, " =");
			if (pEnd == NULL)
			{
				// error
				if (pi->erorr_occur == false)
				{
					pi->erorr_occur = true;
					pi->error_pointer = xml;
					pi->error_code = PIE_ATTR_NO_VALUE;
					//pi->error_string.Format( _T("<%s> attribute has error "), name );
					std::ostringstream os;
					os << "<" << name << "> attribute has error " ;
					pi->error_string = os.str();
				}
				return NULL;
			}

			LPXAttr attr = new XAttr;
			attr->parent = this;

			// XML Attr Name
			_SetString(xml, pEnd, attr->name);

			// add new attribute
			attrs.push_back(attr);
			xml = pEnd;

			// XML Attr Value
			if (xml = _tcsskip(xml))
			{
				//if( xml = _tcschr( xml, '=' ) )
				if (*xml == '=')
				{
					if (xml = _tcsskip(++xml))
					{
						// if " or '
						// or none quote
						int quote = *xml;
						if (quote == '"' || quote == '\'')
							pEnd = _tcsechr(++xml, quote, chXMLEscape);
						else
						{
							//attr= value> 
							// none quote mode
							//pEnd = _tcsechr( xml, ' ', '\\' );
							pEnd = _tcsepbrk(xml, " >", chXMLEscape);
						}

						bool trim = pi->trim_value;
						char escape = pi->escape_value;
						//_SetString( xml, pEnd, &attr->value, trim, chXMLEscape );	
						_SetString(xml, pEnd, attr->value, trim, escape);
						xml = pEnd;
						// ATTRVALUE 
						if (pi->entity_value && pi->entitys)
						{
							//attr->value = pi->entitys->Ref2Entity(attr->value);
							attr->value = pi->entitys->Ref2Entity(const_cast<char*>(attr->value.c_str()));
                            attr->value = attr->value.c_str();
						}

						if (quote == '"' || quote == '\'')
							xml++;
					}
				}
			}
		}
	}

	// not wel-formed tag
	return NULL;
}

// attr1="value1" attr2='value2' attr3=value3 />
//  										  ^- return pointer
//========================================================
// Name   : LoadAttributes
// Desc   : loading attribute plain xml text
// Param  : pszAttrs - xml of attributes
//  		pszEnd - last string
//  		pi = parser information
// Return : advanced string pointer. (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2004-06-14
//========================================================
char* XNode::LoadAttributes(const char* pszAttrs, const char* pszEnd,
	LPPARSEINFO pi /*= &piDefault*/)
{
	char* xml = (char*) pszAttrs;

	while (xml && *xml)
	{
		if (xml = _tcsskip(xml))
		{
			// close tag
			if (xml >= pszEnd)
				// wel-formed tag
				return xml;

			// XML Attr Name
			char* pEnd = strpbrk(xml, " =");
			if (pEnd == NULL)
			{
				// error
				if (pi->erorr_occur == false)
				{
					pi->erorr_occur = true;
					pi->error_pointer = xml;
					pi->error_code = PIE_ATTR_NO_VALUE;
					//pi->error_string.Format( _T("<%s> attribute has error "), name );
					std::ostringstream os;
					os << "<" << name << "> attribute has error " ;
					pi->error_string = os.str();
				}
				return NULL;
			}

			LPXAttr attr = new XAttr;
			attr->parent = this;

			// XML Attr Name
			_SetString(xml, pEnd, attr->name);

			// add new attribute
			attrs.push_back(attr);
			xml = pEnd;

			// XML Attr Value
			if (xml = _tcsskip(xml))
			{
				//if( xml = _tcschr( xml, '=' ) )
				if (*xml == '=')
				{
					if (xml = _tcsskip(++xml))
					{
						// if " or '
						// or none quote
						int quote = *xml;
						if (quote == '"' || quote == '\'')
							pEnd = _tcsechr(++xml, quote, chXMLEscape);
						else
						{
							//attr= value> 
							// none quote mode
							//pEnd = _tcsechr( xml, ' ', '\\' );
							pEnd = _tcsepbrk(xml, " >", chXMLEscape);
						}

						bool trim = pi->trim_value;
						char escape = pi->escape_value;
						//_SetString( xml, pEnd, &attr->value, trim, chXMLEscape );	
						_SetString(xml, pEnd, attr->value, trim, escape);
						xml = pEnd;
						// ATTRVALUE 
						if (pi->entity_value && pi->entitys)
						{
							attr->value = pi->entitys->Ref2Entity(const_cast<char*>(attr->value.c_str()));
							attr->value = attr->value.c_str();
						}

						if (quote == '"' || quote == '\'')
							xml++;
					}
				}
			}
		}
	}

	// not wel-formed tag
	return NULL;
}

// <?xml version="1.0"?>
//  					^- return pointer
//========================================================
// Name   : LoadProcessingInstrunction
// Desc   : loading processing instruction
// Param  : pszXml - PI string
//  		pi - parser information
// Return : advanced string pointer. (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2004-06-14
//========================================================
char* XNode::LoadProcessingInstrunction(const char* pszXml,
	LPPARSEINFO pi /*= &piDefault*/)
{
	// find the end of pi
	char* end = _tcsenistr(pszXml, szXMLPIClose, sizeof(szXMLPIClose) - 1,
					pi ? pi->escape_value : 0);
	if (end == NULL)
		return NULL;

	// process pi
	if (doc)
	{
		char* xml = (char*) pszXml;

		LPXNode node = new XNode;
		node->parent = this;
		node->doc = doc;
		node->type = XNODE_PI;

		xml += sizeof(szXMLPIOpen) - 1;
		char* pTagEnd = strpbrk(xml, " ?>");
		_SetString(xml, pTagEnd, node->name);
		xml = pTagEnd;

		node->LoadAttributes(xml, end, pi);

		doc->childs.push_back(node);
	}

	end += sizeof(szXMLPIClose) - 1;
	return end;
}

// <!-- comment -->
//  			   ^- return pointer
//========================================================
// Name   : LoadComment
// Desc   : loading comment
// Param  : pszXml - comment string
//  		pi - parser information
// Return : advanced string pointer. (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2004-06-14
//========================================================
char* XNode::LoadComment(const char* pszXml, LPPARSEINFO pi /*= &piDefault*/)
{
	// find the end of comment
	char* end = _tcsenistr(pszXml, szXMLCommentClose,
					sizeof(szXMLCommentClose) - 1, pi ? pi->escape_value : 0);
	if (end == NULL)
		return NULL;

	// process comment
	LPXNode par = parent;
	if (parent == NULL && doc)
		par = (LPXNode) & doc;
	if (par)
	{
		char* xml = (char*) pszXml;
		xml += sizeof(szXMLCommentOpen) - 1;

		LPXNode node = new XNode;
		node->parent = this;
		node->doc = doc;
		node->type = XNODE_COMMENT;
		node->name = "#COMMENT";
		_SetString(xml, end, node->value, false);

		par->childs.push_back(node);
	}

	end += sizeof(szXMLCommentClose) - 1;
	return end;
}

// <![CDATA[ cdata ]]>
//  				  ^- return pointer
//========================================================
// Name   : LoadCDATA
// Desc   : loading CDATA
// Param  : pszXml - CDATA string
//  		pi - parser information
// Return : advanced string pointer. (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2004-06-14
//========================================================
char* XNode::LoadCDATA(const char* pszXml, LPPARSEINFO pi /*= &piDefault*/)
{
	// find the end of CDATA
	char* end = _tcsenistr(pszXml, szXMLCDATAClose,
					sizeof(szXMLCDATAClose) - 1, pi ? pi->escape_value : 0);
	if (end == NULL)
		return NULL;

	// process CDATA
	LPXNode par = parent;
	if (parent == NULL && doc)
		par = (LPXNode) & doc;
	if (par)
	{
		char* xml = (char*) pszXml;
		xml += sizeof(szXMLCDATAOpen) - 1;

		LPXNode node = new XNode;
		node->parent = this;
		node->doc = doc;
		node->type = XNODE_CDATA;
		node->name = "#CDATA";
		_SetString(xml, end, node->value, false);

		par->childs.push_back(node);
	}

	end += sizeof(szXMLCDATAClose) - 1;
	return end;
}

//========================================================
// Name   : LoadOtherNodes
// Desc   : internal function for loading PI/CDATA/Comment
// Param  : node - current xml node
//  		pbRet - error occur
//  		pszXml - CDATA string
//  		pi - parser information
// Return : advanced string pointer. (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2004-06-14
//========================================================
char* LoadOtherNodes(LPXNode node, bool* pbRet, const char* pszXml,
	LPPARSEINFO pi /*= &piDefault*/)
{
	char* xml = (char*) pszXml;
	bool do_other_type = true;
	*pbRet = false;

	while (xml && do_other_type)
	{
		do_other_type = false;

		xml = _tcsskip(xml);
		char* prev = xml;
		// is PI( Processing Instruction ) Node?
		if (_tcsnicmp(xml, szXMLPIOpen, sizeof(szXMLPIOpen) - 1) == 0)
		{
			// processing instrunction parse
			// return pointer is next node of pi
			xml = node->LoadProcessingInstrunction(xml, pi);
			//if( xml == NULL )
			//	return NULL;
			// restart xml parse
		}

		if (xml != prev)
			do_other_type = true;
		xml = _tcsskip(xml);
		prev = xml;

		// is comment Node?
		if (_tcsnicmp(xml, szXMLCommentOpen, sizeof(szXMLCommentOpen) - 1) ==
			0)
		{
			// processing comment parse
			// return pointer is next node of comment
			xml = node->LoadComment(xml, pi);
			// comment node is terminal node
			if (node->parent && node->parent->type != XNODE_DOC && xml != prev)
			{
				*pbRet = true;
				return xml;
			}
			// restart xml parse when this node is root doc node
		}

		if (xml != prev)
			do_other_type = true;

		xml = _tcsskip(xml);
		prev = xml;
		// is CDATA Node?
		if (_tcsnicmp(xml, szXMLCDATAOpen, sizeof(szXMLCDATAOpen) - 1) == 0)
		{
			// processing CDATA parse
			// return pointer is next node of CDATA
			xml = node->LoadCDATA(xml, pi);
			// CDATA node is terminal node
			if (node->parent && node->parent->type != XNODE_DOC && xml != prev)
			{
				*pbRet = true;
				return xml;
			}
			// restart xml parse when this node is root doc node
		}

		if (xml != prev)
			do_other_type = true;
	}

	return xml;
}

// <TAG attr1="value1" attr2='value2' attr3=value3 >
// </TAG>
// or
// <TAG />
//  	  ^- return pointer
//========================================================
// Name   : Load
// Desc   : load xml plain text
// Param  : pszXml - plain xml text
//  		pi = parser information
// Return : advanced string pointer  (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* XNode::Load(const char* pszXml, LPPARSEINFO pi /*= &piDefault*/)
{
	// Close it
	Close();

	char* xml = (char*) pszXml;

	xml = strchr(xml, chXMLTagOpen);
	if (xml == NULL)
		return NULL;

	// Close Tag
	if (*(xml + 1) == chXMLTagPre) // </Close
		return xml;

	// Load Other Node before <Tag>(pi, comment, CDATA etc)
	bool bRet = false;
	char* ret = NULL;
	ret = LoadOtherNodes(this, &bRet, xml, pi);
	if (ret != NULL)
		xml = ret;
	if (bRet)
		return xml;

	// XML Node Tag Name Open
	xml++;
	char* pTagEnd = strpbrk(xml, " />\t\r\n");
	_SetString(xml, pTagEnd, name);
	xml = pTagEnd;
	// Generate XML Attributte List
	if (xml = LoadAttributes(xml, pi))
	{
		// alone tag <TAG ... />
		if (*xml == chXMLTagPre)
		{
			xml++;
			if (*xml == chXMLTagClose)
				// wel-formed tag
				return ++xml;
			else
			{
				// error: <TAG ... / >
				if (pi->erorr_occur == false)
				{
					pi->erorr_occur = true;
					pi->error_pointer = xml;
					pi->error_code = PIE_ALONE_NOT_CLOSED;
					// pi->error_string = _T("Element must be closed.");
					std::ostringstream os;
					os << "Element must be closed." ;
					pi->error_string = os.str();
				}
				// not wel-formed tag
				return NULL;
			}
		}
		else
			// open/close tag <TAG ..> ... </TAG>
			//  					  ^- current pointer
		{
			// if text value is not exist, then assign value
			//if( this->value.IsEmpty() || this->value == EMPTY_CSTRING )
			if (XIsEmptyString(const_cast<char*>(value.c_str())))
			{
				// Text Value 
				char* pEnd = _tcsechr(++xml, chXMLTagOpen, chXMLEscape);
				if (pEnd == NULL)
				{
					if (pi->erorr_occur == false)
					{
						pi->erorr_occur = true;
						pi->error_pointer = xml;
						pi->error_code = PIE_NOT_CLOSED;
						//pi->error_string.Format(_T("%s must be closed with </%s>"), name );
						std::ostringstream os;
						os <<
							name <<
							" must be closed with </" <<
							name <<
							">";
						pi->error_string = os.str();
					}
					// error cos not exist CloseTag </TAG>
					return NULL;
				}

				bool trim = pi->trim_value;
				char escape = pi->escape_value;
				//_SetString( xml, pEnd, &value, trim, chXMLEscape );
				_SetString(xml, pEnd, value, trim, escape);

				xml = pEnd;
				// TEXTVALUE reference
				if (pi->entity_value && pi->entitys)
				{
					value = pi->entitys->Ref2Entity(const_cast<char*>(value.c_str()));
					//value = value.c_str();  //当时因文本数据相加出现无法相加的问题才加上，目的是去除\0后面的东西，但现在因此问使用时出现了问题，所以去掉
					std::string sTempValue;
					sTempValue = value.c_str();
					value = sTempValue;
				}
			}

			// generate child nodes
			while (xml && *xml)
			{
				LPXNode node = new XNode;
				node->parent = this;
				node->doc = doc;
				node->type = type;

				xml = node->Load(xml, pi);
				if (node->name.empty() == false)
				{
					childs.push_back(node);
				}
				else
				{
					delete node;
				}

				// open/close tag <TAG ..> ... </TAG>
				//  						   ^- current pointer
				// CloseTag case
				if (xml &&
					*xml &&
					*(xml + 1) &&
					*xml == chXMLTagOpen &&
					*(xml + 1) == chXMLTagPre)
				{
					// </Close>
					xml += 2; // C

					if (xml = _tcsskip(xml))
					{
						std::string closename;
						char* pEnd = strpbrk(xml, " >");
						if (pEnd == NULL)
						{
							if (pi->erorr_occur == false)
							{
								pi->erorr_occur = true;
								pi->error_pointer = xml;
								pi->error_code = PIE_NOT_CLOSED;
								//pi->error_string.Format(_T("it must be closed with </%s>"), name );
								std::ostringstream os;
								os << "it must be closed with </" << name
									<< ">";
								pi->error_string = os.str();
							}
							// error
							return NULL;
						}
						_SetString(xml, pEnd, closename);
						//if( closename == this->name )
						if (0 == strcmp(closename.c_str(), this->name.c_str()))
						{
							// wel-formed open/close
							xml = pEnd + 1;
							// return '>' or ' ' after pointer
							return xml;
						}
						else
						{
							xml = pEnd + 1;
							// 2004.6.15 - example <B> alone tag
							// now it can parse with attribute 'force_arse'
							if (pi->force_parse == false)
							{
								// not welformed open/close
								if (pi->erorr_occur == false)
								{
									pi->erorr_occur = true;
									pi->error_pointer = xml;
									pi->error_code = PIE_NOT_NESTED;
									//pi->error_string.Format(_T("'<%s> ... </%s>' is not wel-formed."), name, closename );
									std::ostringstream os;
									os << "'<" << name << "> ... </"
										<< closename
										<< ">' is not wel-formed.";
									pi->error_string = os.str();
								}
								return NULL;
							}
						}
					}
				}
				else	// Alone child Tag Loaded
					// else 锟斤拷洗锟斤拷凭锟较达拷锟斤拷砂锟?
				{
					//if( xml && this->value.IsEmpty() && *xml !=chXMLTagOpen )
					if (xml &&
						XIsEmptyString(const_cast<char*>(value.c_str())) &&
						*xml != chXMLTagOpen)
					{
						// Text Value 
						char* pEnd = _tcsechr(xml, chXMLTagOpen, chXMLEscape);
						if (pEnd == NULL)
						{
							// error cos not exist CloseTag </TAG>
							if (pi->erorr_occur == false)
							{
								pi->erorr_occur = true;
								pi->error_pointer = xml;
								pi->error_code = PIE_NOT_CLOSED;
								//pi->error_string.Format(_T("it must be closed with </%s>"), name );
								std::ostringstream os;
								os << "it must be closed with </" << name
									<< ">";
								pi->error_string = os.str();
							}
							return NULL;
						}

						bool trim = pi->trim_value;
						char escape = pi->escape_value;
						//_SetString( xml, pEnd, &value, trim, chXMLEscape );
						_SetString(xml, pEnd, value, trim, escape);

						xml = pEnd;
						//TEXTVALUE
						if (pi->entity_value && pi->entitys)
						{
							value = pi->entitys->Ref2Entity(const_cast<char*>(value.c_str()));
							value = value.c_str();
						}
					}
				}
			}
		}
	}

	return xml;
}

// <?xml version='1.0'?>
// <TAG attr1="value1" attr2='value2' attr3=value3 >
// </TAG>
// or
// <TAG />
//  	  ^- return pointer
//========================================================
// Name   : Load
// Desc   : load xml plain text for xml document
// Param  : pszXml - plain xml text
//  		pi = parser information
// Return : advanced string pointer  (error return NULL)
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
char* _tagXMLDocument::Load(const char* pszXml, LPPARSEINFO pi /*= NULL*/)
{
	LPXNode node = new XNode;
	node->parent = (LPXNode)this;
	node->type = XNODE_ELEMENT;
	node->doc = this;
	char* end;

	if (pi == NULL)
		pi = &parse_info;

	if ((end = node->Load(pszXml, pi)) == NULL)
	{
		delete node;
		return NULL;
	}

	childs.push_back(node);

	// Load Other Node after </Tag>(pi, comment, CDATA etc)
	char* ret;
	bool bRet = false;
	ret = LoadOtherNodes(node, &bRet, end, pi);
	if (ret != NULL)
		end = ret;

	return end;
}

LPXNode _tagXMLDocument::GetRoot()
{
	XNodes::iterator it = childs.begin();
	for (; it != childs.end() ; ++(it))
	{
		LPXNode node = *it;
		if (node->type == XNODE_ELEMENT)
			return node;
	}
	return NULL;
}

//========================================================
// Name   : GetXML
// Desc   : convert plain xml text from parsed xml attirbute
// Param  :
// Return : converted plain string
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
std::string _tagXMLAttr::GetXML(LPDISP_OPT opt /*= &optDefault*/)
{
	std::ostringstream os;
	//os << (const char*)name << "='" << (const char*)value << "' ";

	os <<
		name <<
		"=" <<
		(char)
		opt->value_quotation_mark
		<<
		(opt->reference_value &&
		opt->entitys ?
		opt->entitys->Entity2Ref(const_cast<char*>(value.c_str())) :
		value)
		<<
		(char)
		opt->value_quotation_mark <<
		" ";
	//return os.str().c_str();
	return os.str();
}

//========================================================
// Name   : GetXML
// Desc   : convert plain xml text from parsed xml node
// Param  :
// Return : converted plain string
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
std::string XNode::GetXML(LPDISP_OPT opt /*= &optDefault*/)
{
	std::ostringstream os;

	// tab
	if (opt && opt->newline)
	{
		if (opt && opt->newline)
			os << "\r\n";
		for (int i = 0 ; i < opt->tab_base ; i++)
			os << '\t';
	}

	if (type == XNODE_DOC)
	{
		for (unsigned  int i = 0; i < childs.size(); i++)
			os << childs[i]->GetXML(opt);
		//return os.str().c_str();
		return os.str();
	}
	else if (type == XNODE_PI)
	{
		// <?TAG
		os << szXMLPIOpen << name;
		// <?TAG Attr1="Val1" 
		if (attrs.empty() == false)
			os << ' ';
		for (unsigned int i = 0; i < attrs.size(); i++)
		{
			os << attrs[i]->GetXML(opt);
		}
		//?>
		os << szXMLPIClose;	
		//return os.str().c_str();
		return os.str();
	}
	else if (type == XNODE_COMMENT)
	{
		// <--comment
		os << szXMLCommentOpen << value;
		//-->
		os << szXMLCommentClose;	
		//return os.str().c_str();
		return os.str();
	}
	else if (type == XNODE_CDATA)
	{
		// <--comment
		os << szXMLCDATAOpen << value;
		//-->
		os << szXMLCDATAClose;	
		//return os.str().c_str();
		return os.str();
	}

	// <TAG
	os << '<' << name;

	// <TAG Attr1="Val1" 
	if (attrs.empty() == false)
		os << ' ';
	for (unsigned int i = 0; i < attrs.size(); i++)
	{
		os << attrs[i]->GetXML(opt);
	}

	if (childs.empty() && value.empty())
	{
		// <TAG Attr1="Val1"/> alone tag 
		os << "/>";
	}
	else
	{
		// <TAG Attr1="Val1"> and get child
		os << '>';
		if (opt && opt->newline && !childs.empty())
		{
			opt->tab_base++;
		}

		for (unsigned int i = 0; i < childs.size(); i++)
			os << childs[i]->GetXML(opt);

		// Text Value
		//if( value != EMPTY_CSTRING )
		if (strcmp(value.c_str(), ""))
		{
			if (opt && opt->newline && !childs.empty())
			{
				if (opt && opt->newline)
					os << "\r\n";
				for (int i = 0 ; i < opt->tab_base ; i++)
					os << '\t';
			}
			os <<
				(opt->reference_value &&
				opt->entitys ?
				opt->entitys->Entity2Ref(const_cast<char*>(value.c_str())) :
				value);
		}

		// </TAG> CloseTag
		if (opt && opt->newline && !childs.empty())
		{
			os << "\r\n";
			for (int i = 0 ; i < opt->tab_base - 1 ; i++)
				os << '\t';
		}
		os << "</" << name << '>';

		if (opt && opt->newline)
		{
			if (!childs.empty())
				opt->tab_base--;
		}
	}

	//return os.str().c_str();
	return os.str();
}

//========================================================
// 锟斤拷 : GetText
//   锟? 锟?锟?锟狡?锟斤拷锟?
// 锟? 锟?:
// 锟?: 券锟斤拷
//--------------------------------------------------------
// 锟斤拷   锟斤拷  			   锟斤拷/
// v锟?  2004-06-15
//========================================================
std::string XNode::GetText(LPDISP_OPT opt /*= &optDefault*/)
{
	std::ostringstream os;

	if (type == XNODE_DOC)
	{
		for (unsigned int i = 0; i < childs.size(); i++)
			os << childs[i]->GetText(opt);
	}
	else if (type == XNODE_PI)
	{
		// no text
	}
	else if (type == XNODE_COMMENT)
	{
		// no text
	}
	else if (type == XNODE_CDATA)
	{
		os << value;
	}
	else if (type == XNODE_ELEMENT)
	{
		if (childs.empty() && value.empty())
		{
			// no text
		}
		else
		{
			// childs text
			for (unsigned int i = 0; i < childs.size(); i++)
				os << childs[i]->GetText();

			// Text Value
			os <<
				(opt->reference_value &&
				opt->entitys ?
				opt->entitys->Entity2Ref(const_cast<char*>(value.c_str())) :
				value);
		}
	}

	return os.str();
}

//========================================================
// Name   : GetAttr
// Desc   : get attribute with attribute name
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXAttr XNode::GetAttr(const char* attrname)
{
	for (unsigned int i = 0; i < attrs.size(); i++)
	{
		LPXAttr attr = attrs[i];
		if (attr)
		{
			if (0 == strcmp(attr->name.c_str(), attrname))
			{
				return attr;
			}
			//if( attr->name == attrname )
			//	return attr;
		}
	}
	return NULL;
}

//========================================================
// Name   : GetAttrs
// Desc   : find attributes with attribute name, return its list
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
XAttrs XNode::GetAttrs(const char* name)
{
	XAttrs attrs;
	for (unsigned int i = 0; i < attrs.size(); i++)
	{
		LPXAttr attr = attrs[i];
		if (attr)
		{
			if (0 == strcmp(attr->name.c_str(), name))
			{
				attrs.push_back(attr);
			}
			//if( attr->name == name )
			//	attrs.push_back( attr );
		}
	}
	return attrs;
}

//========================================================
// Name   : GetAttrValue
// Desc   : get attribute with attribute name, return its value
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
const char* XNode::GetAttrValue(const char* attrname)
{
	LPXAttr attr = GetAttr(attrname);
	return attr ? (const char *) attr->value.c_str() : NULL;
}

XNodes XNode::GetChilds()
{
	return childs;
}

//========================================================
// Name   : GetChilds
// Desc   : Find childs with name and return childs list
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
XNodes XNode::GetChilds(const char* name)
{
	XNodes nodes;
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		LPXNode node = childs[i];
		if (node)
		{
			//if( 0 == node->name.compare(name) )
			if (0 == strcmp(node->name.c_str(), name))
			{
				nodes.push_back(node);
			}
			/*
											if( node->name == name )
												nodes.push_back( node );
											*/
		}
	}
	return nodes;
}

//========================================================
// Name   : GetChild
// Desc   : get child node with index
// Param  :
// Return : NULL return if no child.
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::GetChild(int i)
{
	if (i >= 0 && i < childs.size())
		return childs[i];
	return NULL;
}

//========================================================
// Name   : GetChildCount
// Desc   : get child node count
// Param  :
// Return : 0 return if no child
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-12-26
//========================================================
int XNode::GetChildCount()
{
	return childs.size();
}

//========================================================
// Name   : GetChild
// Desc   : Find child with name and return child
// Param  :
// Return : NULL return if no child.
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::GetChild(const char* name)
{
	for (unsigned int i = 0; i < childs.size(); i++)
	{
		LPXNode node = childs[i];
		if (node)
		{
			if (0 == strcmp(node->name.c_str(), name))
			{
				return node;
			}
			//if( node->name == name )
			//	return node;
		}
	}
	return NULL;
}

//========================================================
// Name   : GetChildValue
// Desc   : Find child with name and return child's value
// Param  :
// Return : NULL return if no child.
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
const char* XNode::GetChildValue(const char* name)
{
	LPXNode node = GetChild(name);
	//return (node != NULL) ? (const char *) node->value.c_str() : NULL;
    return (node != NULL) ? (const char *) node->value.c_str() : "";
}

std::string XNode::GetChildText(const char* name,
	LPDISP_OPT opt /*= &optDefault*/)
{
	LPXNode node = GetChild(name);
	return (node != NULL) ? node->GetText(opt) : "";
}

LPXAttr XNode::GetChildAttr(const char* name, const char* attrname)
{
	LPXNode node = GetChild(name);
	return node ? node->GetAttr(attrname) : NULL;
}

const char* XNode::GetChildAttrValue(const char* name, const char* attrname)
{
	LPXAttr attr = GetChildAttr(name, attrname);
	return attr ? (const char *) attr->value.c_str() : NULL;
}

//========================================================
// Name   : Find
// Desc   : find node with tag name from it's all childs
// Param  :
// Return : NULL return if no found node.
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::Find(const char* name)
{
	XNodes::iterator it = childs.begin();
	for (; it != childs.end(); ++(it))
	{
		LPXNode child = *it;
		//if( child->name == name )
		//	return child;
		if (0 == strcmp(child->name.c_str(), name))
		{
			return child;
		}

		XNodes::iterator it = child->childs.begin();
		for (; it != child->childs.end(); ++(it))
		{
			LPXNode find = child->Find(name);
			if (find != NULL)
				return find;
		}
	}

	return NULL;
}

//========================================================
// Name   : GetChildIterator
// Desc   : get child nodes iterator
// Param  :
// Return : NULL return if no childs.
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
XNodes::iterator XNode::GetChildIterator(LPXNode node)
{
	XNodes::iterator it = childs.begin();
	for (; it != childs.end() ; ++(it))
	{
		if (*it == node)
			return it;
	}
	//return NULL;
	return childs.end();
}

//========================================================
// Name   : AppendChild
// Desc   : add node
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::AppendChild(const char* name /*= NULL*/,
	const char* value /*= NULL*/)
{
	return AppendChild(CreateNode(name, value));
}

//========================================================
// Name   : AppendChild
// Desc   : add node
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::AppendChild(LPXNode node)
{
	node->parent = this;
	node->doc = doc;
	childs.push_back(node);
	return node;
}

//========================================================
// Name   : RemoveChild
// Desc   : detach node and delete object
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
bool XNode::RemoveChild(LPXNode node)
{
	XNodes::iterator it = GetChildIterator(node);
	if (it != childs.end())
	{
		delete * it;
		childs.erase(it);
		return true;
	}
	return false;
}

int XNode::GetAttrCount()
{
	return attrs.size();
}
//========================================================
// Name   : GetAttr
// Desc   : get attribute with index in attribute list
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXAttr XNode::GetAttr(int i)
{
	if (i >= 0 && i < attrs.size())
		return attrs[i];
	return NULL;
}

//========================================================
// Name   : GetAttrIterator
// Desc   : get attribute iterator
// Param  : 
// Return : std::vector<LPXAttr>::iterator
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
XAttrs::iterator XNode::GetAttrIterator(LPXAttr attr)
{
	XAttrs::iterator it = attrs.begin();
	for (; it != attrs.end() ; ++(it))
	{
		if (*it == attr)
			return it;
	}
	//return NULL;
	return attrs.end();
}

//========================================================
// Name   : AppendAttr
// Desc   : add attribute
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXAttr XNode::AppendAttr(LPXAttr attr)
{
	attr->parent = this;
	attrs.push_back(attr);
	return attr;
}

//========================================================
// Name   : RemoveAttr
// Desc   : detach attribute and delete object
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
bool XNode::RemoveAttr(LPXAttr attr)
{
	XAttrs::iterator it = GetAttrIterator(attr);
	if (it != attrs.end())
	{
		delete * it;
		attrs.erase(it);
		return true;
	}
	return false;
}

//========================================================
// Name   : CreateNode
// Desc   : Create node object and return it
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::CreateNode(const char* name /*= NULL*/,
	const char* value /*= NULL*/)
{
	LPXNode node = new XNode;
	node->name = name;
	node->value = value;
	return node;
}

//========================================================
// Name   : CreateAttr
// Desc   : create Attribute object and return it
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXAttr XNode::CreateAttr(const char* name /*= NULL*/,
	const char* value /*= NULL*/)
{
	LPXAttr attr = new XAttr;
	attr->name = name;
	attr->value = value;
	return attr;
}

//========================================================
// Name   : AppendAttr
// Desc   : add attribute
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXAttr XNode::AppendAttr(const char* name /*= NULL*/,
	const char* value /*= NULL*/)
{
	return AppendAttr(CreateAttr(name, value));
}

//========================================================
// Name   : DetachChild
// Desc   : no delete object, just detach in list
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::DetachChild(LPXNode node)
{
	XNodes::iterator it = GetChildIterator(node);
	if (it != childs.end())
	{
		childs.erase(it);
		return node;
	}
	return NULL;
}

//========================================================
// Name   : DetachAttr
// Desc   : no delete object, just detach in list
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXAttr XNode::DetachAttr(LPXAttr attr)
{
	XAttrs::iterator it = GetAttrIterator(attr);
	if (it != attrs.end())
	{
		attrs.erase(it);
		return attr;
	}
	return NULL;
}

//========================================================
// Name   : CopyNode
// Desc   : copy current level node with own attributes
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
void XNode::CopyNode(LPXNode node)
{
	Close();

	doc = node->doc;
	parent = node->parent;
	name = node->name;
	value = node->value;
	type = node->type;

	// copy attributes
	for (unsigned int i = 0; i < node->attrs.size(); i++)
	{
		LPXAttr attr = node->attrs[i];
		if (attr)
			AppendAttr(attr->name.c_str(), attr->value.c_str());
	}
}

//========================================================
// Name   : _CopyBranch
// Desc   : recursive internal copy branch 
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
void XNode::_CopyBranch(LPXNode node)
{
	CopyNode(node);

	for (unsigned int i = 0; i < node->childs.size(); i++)
	{
		LPXNode child = node->childs[i];
		if (child)
		{
			LPXNode mychild = new XNode;
			mychild->CopyNode(child);
			AppendChild(mychild);

			mychild->_CopyBranch(child);
		}
	}
}

//========================================================
// Name   : AppendChildBranch
// Desc   : add child branch ( deep-copy )
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
LPXNode XNode::AppendChildBranch(LPXNode node)
{
	LPXNode child = new XNode;
	child->CopyBranch(node);

	return AppendChild(child);
}

//========================================================
// Name   : CopyBranch
// Desc   : copy branch ( deep-copy )
// Param  :
// Return : 
//--------------------------------------------------------
// Coder	Date					  Desc
// bro  	2002-10-29
//========================================================
void XNode::CopyBranch(LPXNode branch)
{
	Close();

	_CopyBranch(branch);
}


_tagXMLEntitys::_tagXMLEntitys(LPXENTITY entities, int count)
{
	for (int i = 0; i < count; i++)
		push_back(entities[i]);
}

LPXENTITY _tagXMLEntitys::GetEntity(int entity)
{
	for (unsigned int i = 0; i < size(); i++)
	{
		if (at(i).entity == entity)
			return LPXENTITY(&at(i));
	}
	return NULL;
}

LPXENTITY _tagXMLEntitys::GetEntity(char* entity)
{
	for (unsigned int i = 0; i < size(); i++)
	{
		char* ref = (char*) at(i).ref;
		char* ps = entity;
		while (ref && *ref)
			if (*ref++ != *ps++)
				break;
		if (ref && !*ref)	// found!
			return LPXENTITY(&at(i));
	}
	return NULL;
}

int _tagXMLEntitys::GetEntityCount(const char* str)
{
	int nCount = 0;
	char* ps = (char*) str;
	while (ps && *ps)
		if (GetEntity(*ps++))
			nCount ++;
	return nCount;
}

int _tagXMLEntitys::Ref2Entity(const char* estr, char* str, int strlen)
{
	char* pes = (char*) estr;
	char* ps = str;
	char* ps_end = ps + strlen;
	while (pes && *pes && ps < ps_end)
	{
		LPXENTITY ent = GetEntity(pes);
		if (ent)
		{
			// copy entity meanning char
			*ps = ent->entity;
			pes += ent->ref_len;
		}
		else
			*ps = *pes++;	// default character copy
		ps++;
	}
	*ps = '\0';

	// total copied characters
	return ps - str;
}

int _tagXMLEntitys::Entity2Ref(const char* str, char* estr, int estrlen)
{
	char* ps = (char*) str;
	char* pes = (char*) estr;
	char* pes_end = pes + estrlen;
	while (ps && *ps && pes < pes_end)
	{
		LPXENTITY ent = GetEntity(*ps);
		if (ent)
		{
			// copy entity string
			char* ref = (char*) ent->ref;
			while (ref && *ref)
				*pes++ = *ref++;
		}
		else
			*pes++ = *ps;	// default character copy
		ps++;
	}
	*pes = '\0';

	// total copied characters
	return pes - estr;
}

std::string _tagXMLEntitys::Ref2Entity(const char* estr)
{
	std::string es;
	if (estr)
	{
		int len = strlen(estr);
		es.resize(len + 1);
		//char* esbuf = es.GetBufferSetLength( len+1 );
		char* esbuf = const_cast<char*>(es.c_str());
		if (esbuf)
			Ref2Entity(estr, esbuf, len);
	}
	return es;
}

std::string _tagXMLEntitys::Entity2Ref(const char* str)
{
	std::string s;
	if (str)
	{
		int nEntityCount = GetEntityCount(str);
		if (nEntityCount == 0)
		{
			//return CString(str);
			s = str;
			return s;
		}
		int len = strlen(str) + nEntityCount*10 ;
		s.resize(len + 1);
		//char* sbuf = s.GetBufferSetLength( len+1 );
		char* sbuf = const_cast<char*>(s.c_str());
		if (sbuf)
			Entity2Ref(str, sbuf, len);
	}
	return s;
}

std::string XRef2Entity(const char* estr)
{
	return entityDefault.Ref2Entity(estr);
}

std::string XEntity2Ref(const char* str)
{
	return entityDefault.Entity2Ref(str);
}

bool XIsEmptyString(const char* str)
{
	std::string s;
	s = str;
	TrimLeft(s);
	TrimRight(s);

	//return ( s.empty() || s == EMPTY_CSTRING );
	return (s.empty() || (0 == strcmp(s.c_str(), "")));
}