/* CirKit: A circuit toolkit
 * Copyright (C) 2009-2015  University of Bremen
 * Copyright (C) 2015-2016  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "xmg_random_rewrite.hpp"

#include <random>

#include <core/utils/timer.hpp>
#include <classical/xmg/xmg_rewrite.hpp>

namespace cirkit
{

xmg_graph xmg_random_rewrite( const xmg_graph& xmg,
                              const properties::ptr& settings,
                              const properties::ptr& statistics )
{
  // (1) parse settings
  const auto seed                = get( settings, "seed",              51966u );
  const auto replace_probability = get( settings, "replace_prability", 10u );

  // (2) write runtime information into statistics
  properties_timer t( statistics );

  // (3) create a roll dice function
  const auto dice = [seed, replace_probability]() {
    static std::default_random_engine gen( seed );
    static std::uniform_int_distribution<unsigned> dist( 0u, 100u );

    return dist( gen ) <= replace_probability;
  };

  // (4) how to rewrite MAJ and XOR gates
  maj_rewrite_func_t on_maj = [&dice]( xmg_graph& xmg_new,
                                       const xmg_function& a,
                                       const xmg_function& b,
                                       const xmg_function& c  ) {
    return dice() ? xmg_new.get_constant( false ) : xmg_new.create_maj( a, b, c );
  };

  xor_rewrite_func_t on_xor = [&dice]( xmg_graph& xmg_new,
                                       const xmg_function& a,
                                       const xmg_function& b  ) {
    return dice() ? xmg_new.get_constant( true ) : xmg_new.create_xor( a, b );
  };

  // (5) rewrite the XMG
  const auto xmg_tmp = xmg_rewrite_top_down( xmg, on_maj, on_xor );

  // (6) strash rewritten XMG to remove dangling nodes
  return xmg_strash( xmg_tmp );
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
