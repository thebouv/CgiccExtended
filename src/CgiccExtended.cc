#include <map>
#include <string>
#include <sstream>
#include "CgiccExtended.hh"

/* Method: paramMap
* Returns key/value map of all parameters.
* this is like CGI.pm's $cgi->Vars() method
* I just didn't want to call this method Vars
*/
std::map<std::string,std::string> CgiccExtended::paramMap() {
  std::map<std::string,std::string> myMap;
  cgicc::const_form_iterator iter;
  for(iter = this->getElements().begin(); 
     iter != this->getElements().end(); 
     ++iter) {
     myMap[iter->getName()] = iter->getValue();
  }
  return myMap;
}

/* Method: param(std::string paramName)
* Returns the value of a named parameter.
* 
* 
*/
std::string CgiccExtended::param(std::string paramName) {
  std::string myParamValue;
  cgicc::form_iterator myParam = this->getElement(paramName);
  if(myParam != this->getElements().end()) {
     // iterator points to an element with a value
    myParamValue = myParam->getValue();
  }
  else {
    // element either doesn't exist, or was not filled in
    myParamValue = "";
  }
  return myParamValue;
}

/* Operator: CgiccExtended[](std::string paramName);
* Returns the value of a named parameter.
* 
* 
*/
std::string CgiccExtended::operator[](std::string paramName) {
  return this->param(paramName);
}

/* Method: header
* Return a Content-Type: style header
* 
* 
*/
std::string CgiccExtended::header(std::string headerType) {
  std::stringstream myHeader;
  myHeader << cgicc::HTTPContentHeader(headerType);
  return myHeader.str();
}

/* Method: redirect
* Return a Location: style header
* 
* 
*/
std::string CgiccExtended::redirect(std::string redirectLocation) {
  std::stringstream myRedirect;
  myRedirect << cgicc::HTTPRedirectHeader(redirectLocation);
  return myRedirect.str();}

/* Method: dump
* Returns a string in which all the known parameter/value are printed
* mainly for the purposes of debugging
* 
*/
std::string CgiccExtended::dump(std::string delimiter, std::string endline) {
  std::string myDump;
  cgicc::const_form_iterator iter;
  for(iter = this->getElements().begin();
      iter != this->getElements().end();
      ++iter) {
      myDump += iter->getName() + delimiter + iter->getValue() + endline;
  }
  return myDump;
}

/* Method: cookieDump
* Returns a string in which all the known keys/values are printed
* from the cookie, mainly for the purposes of debugging
* 
*/
std::string CgiccExtended::cookieDump(std::string delimiter, std::string endline) {
  std::string myDump;
  const cgicc::CgiEnvironment& env = this->getEnvironment();
  cgicc::const_cookie_iterator iter;
  for(iter = env.getCookieList().begin(); 
      iter != env.getCookieList().end(); 
      ++iter) {
      myDump += iter->getName() + delimiter + iter->getValue() + endline;
  }
  return myDump;
}

/* Method: cookieMap
* Returns key/value map of all cookies.
* 
* 
*/
std::map<std::string,std::string> CgiccExtended::cookieMap() {
  std::map<std::string,std::string> myMap;
  const cgicc::CgiEnvironment& env = this->getEnvironment();
  cgicc::const_cookie_iterator iter;
  for(iter = env.getCookieList().begin(); 
      iter != env.getCookieList().end(); 
      ++iter) {
      myMap[iter->getName()] = iter->getValue();
  }
  return myMap;
}

/* Method: setCookie(std::string myName, std::string myValue)
* Returns a single properly formed Set-Cookie header
* 
* 
*/
std::string CgiccExtended::setCookie(std::string myName, std::string myValue) {
  std::stringstream myCookie;
  myCookie << cgicc::HTTPCookie(myName,myValue) << std::endl;
  return myCookie.str();
}

/* Method: setCookie(std::map<std::string,std::string> &myMap)
* Returns a map of properly formed Set-Cookie headers
* based on the map passed by reference to it
* 
*/
std::string CgiccExtended::setCookie(std::map<std::string,std::string> &myMap) {
  std::stringstream myCookie;
  std::map<std::string,std::string>::iterator the_iterator = myMap.begin();
  while( the_iterator != myMap.end() ) {
    myCookie << cgicc::HTTPCookie((*the_iterator).first,(*the_iterator).second)
      << std::endl;
    the_iterator++;
  }
  return myCookie.str();
}
