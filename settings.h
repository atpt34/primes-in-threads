#ifndef MY_SETTINGS_H
#define MY_SETTINGS_H

Xml_Struct interval_xs {
  Xml_Elem{"<root>","</root>"},
  Xml_Elem{"<intervals>","</intervals>"},
  Xml_Elem{"<interval>","</interval>"},
  std::vector<Xml_Elem> {
    Xml_Elem{"<low>","</low>"},
    Xml_Elem{"<high>","</high>"}
  }
};

Xml_Struct primes_xs {
  Xml_Elem{"<root>","</root>"},
  Xml_Elem{"<primes>","</primes>"},
  Xml_Elem{"<prime>","</prime>"}
};

#endif
