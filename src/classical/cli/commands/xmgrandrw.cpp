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

#include "xmgrandrw.hpp"

#include <core/utils/program_options.hpp>
#include <classical/functions/xmg_random_rewrite.hpp>

namespace cirkit
{

xmgrandrw_command::xmgrandrw_command( const environment::ptr& env )
  : xmg_base_command( env, "Rewrite XMGs randomly" )
{
  opts.add_options()
    ( "seed,s",                value_with_default( &seed ),                "random seed" )
    ( "replace_probability,p", value_with_default( &replace_probability ), "replace probability (value from 0 to 100)" )
    ;
}

bool xmgrandrw_command::execute()
{
  const auto settings = make_settings();
  settings->set( "seed", seed );
  settings->set( "replace_prabibility", replace_probability );

  xmg() = xmg_random_rewrite( xmg(), settings, statistics );

  print_runtime();

  return true;
}

}

// Local Variables:
// c-basic-offset: 2
// eval: (c-set-offset 'substatement-open 0)
// eval: (c-set-offset 'innamespace 0)
// End:
