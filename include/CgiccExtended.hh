#ifndef CGICCEXT_HH
#define CGICCEXT_HH

#include "cgicc/Cgicc.h"
#include "cgicc/HTTPContentHeader.h"
#include "cgicc/HTTPRedirectHeader.h"

class CgiccExtended : public cgicc::Cgicc {
  public:
    // param methods
    std::map<std::string,std::string> paramMap();
    std::string param(std::string paramName);
    std::string operator[](std::string paramName);
    
    // header methods
    std::string header(std::string headerType = "text/html");
    std::string redirect(std::string redirectLocation);

    // cookie methods
    std::map<std::string,std::string> cookieMap();
    std::string setCookie(std::string,std::string);
    std::string setCookie(std::map<std::string,std::string> &);

    // debug methods
    std::string dump(std::string delimiter = " : ",
                     std::string endline = "<br>");
    std::string cookieDump(std::string delimiter = " : ",
                           std::string endline = "<br>");  
};

#endif
