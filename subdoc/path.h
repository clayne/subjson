#if !defined(SUBDOC_PATH_H) && defined(__cplusplus)
#define SUBDOC_PATH_H

#include "subdoc-api.h"
#include "jsonsl_header.h"
#include <string>
#include <list>

// Maximum number of components in a path. Set to 33 to allow 32 'actual'
// components plus the implicit root element.
#define COMPONENTS_ALLOC 33

namespace Subdoc {
class Path {
public:
    typedef jsonsl_jpr_component_st Component;
    typedef jsonsl_jpr_st CompInfo;

    Path();
    ~Path();
    void clear();
    int parse(const char *, size_t);
    int parse(const char *s) { return parse(s, strlen(s)); }
    int parse(const std::string& s) { return parse(s.c_str(), s.size()); }
    void pop_component() { jpr_base.ncomponents--; }
    jsonsl_error_t add_array_index(long ixnum);
    size_t size() const { return jpr_base.ncomponents; }
    Component& get_component(int ix) const { return jpr_base.components[ix]; }
    Component& operator[](size_t ix) const { return get_component(ix); }

    CompInfo jpr_base;
    Component components_s[COMPONENTS_ALLOC];
    bool has_negix; /* True if there is a negative array index in the path */
private:
    inline const char * convert_escaped(const char *src, size_t &len);
    inline int add_num_component(const char *component, size_t len);
    inline int add_str_component(const char *component, size_t len, int n_backtick);
    inline Component& alloc_component(jsonsl_jpr_type_t type);

    std::list<std::string*> m_cached;
    std::list<std::string*> m_used;
};
}

#endif
