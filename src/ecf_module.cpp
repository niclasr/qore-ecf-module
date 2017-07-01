/* The MIT License (MIT)
 *
 * Copyright (c) 2015 - 2017 Niclas Rosenvik <youremailsarecrap@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <config.h>
#include <qore/Qore.h>

#include <ecf_module.h>
#include <ql_ecf.h>

DLLEXPORT char qore_module_name[] = "ecf";
DLLEXPORT char qore_module_version[] = PACKAGE_VERSION;
DLLEXPORT char qore_module_description[] = "extra compression functions module";
DLLEXPORT char qore_module_author[] = "Niclas Rosenvik";
DLLEXPORT char qore_module_url[] = "http://github.com/niclasr/qore-ecf-module";
DLLEXPORT int qore_module_api_major = QORE_MODULE_API_MAJOR;
DLLEXPORT int qore_module_api_minor = QORE_MODULE_API_MINOR;
DLLEXPORT qore_license_t qore_module_license = QL_MIT;
DLLEXPORT qore_module_init_t qore_module_init = ecf_module_init;
DLLEXPORT qore_module_ns_init_t qore_module_ns_init = ecf_module_ns_init;
DLLEXPORT qore_module_delete_t qore_module_delete = ecf_module_delete;


QoreNamespace ECFNS("ecf");

QoreStringNode * ecf_module_init() {
  init_ecf_functions(ECFNS);
  return 0;
}

void ecf_module_ns_init(QoreNamespace *rns, QoreNamespace *qns) {
  qns->addNamespace(ECFNS.copy());
}

void ecf_module_delete() {}
