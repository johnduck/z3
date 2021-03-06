/*
  Copyright (c) 2017 Microsoft Corporation
  Author: Lev Nachmanson
*/
#pragma once
#include "util/lp/lp_settings.h"
namespace lean {
class lar_solver;
class lp_bound_propagator {
    std::unordered_map<unsigned, unsigned> m_improved_low_bounds; // these maps map a column index to the corresponding index in ibounds
    std::unordered_map<unsigned, unsigned> m_improved_upper_bounds;
    lar_solver & m_lar_solver;
public:
    vector<implied_bound> m_ibounds;
public:
    lp_bound_propagator(lar_solver & ls);
    column_type get_column_type(unsigned) const;
    const impq & get_low_bound(unsigned) const;
    const impq & get_upper_bound(unsigned) const;
    void try_add_bound(const mpq & v, unsigned j, bool is_low, bool coeff_before_j_is_pos, unsigned row_or_term_index, bool strict);
    virtual bool bound_is_interesting(unsigned vi,
                                      lean::lconstraint_kind kind,
                                      const rational & bval) {return true;}
    unsigned number_of_found_bounds() const { return m_ibounds.size(); }
    virtual void consume(mpq const& v, unsigned j) { std::cout << "doh\n"; }
};
}
