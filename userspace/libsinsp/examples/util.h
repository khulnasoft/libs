// SPDX-License-Identifier: Apache-2.0
/*
Copyright (C) 2023 The Khulnasoft Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <string>
#include <libsinsp/sinsp.h>

//
// Get the string representation of a ppm_event_category
//
std::string get_event_category_name(ppm_event_category category);

//
// Get the string representation of a ppm_event_type
//
std::string get_event_type_name(sinsp_evt *ev);
