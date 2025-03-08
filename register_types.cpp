/**************************************************************************/
/*  register_types.cpp                                                    */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "register_types.h"

#include "core/object/class_db.h"
#include "src/godot_sqlite.h"
#include "src/node_sqlite.h"
#include "src/resource_loader_sqlite.h"
#include "src/resource_saver_sqlite.h"
#include "src/resource_sqlite.h"
#include "core/io/resource_loader.h"
#include "core/io/resource_saver.h"

static Ref<ResourceFormatLoaderSQLite> sqlite_loader;
static Ref<ResourceFormatSaverSQLite> sqlite_saver;

void initialize_sqlite_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SERVERS) {
		return;
	}
 	sqlite_loader.instantiate();
 	sqlite_saver.instantiate();
 	ResourceLoader::add_resource_format_loader(sqlite_loader);
 	ResourceSaver::add_resource_format_saver(sqlite_saver);
	ClassDB::register_class<SQLiteDatabase>();
	ClassDB::register_class<SQLiteAccess>();
	ClassDB::register_class<SQLiteQuery>();
	ClassDB::register_class<SQLiteQueryResult>();
	ClassDB::register_class<SQLiteColumnSchema>();
	ClassDB::register_class<SQLite>();
}

void uninitialize_sqlite_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SERVERS) {
		return;
	}

	if (sqlite_loader.is_valid()) {
		ResourceLoader::remove_resource_format_loader(sqlite_loader);
		sqlite_loader.unref();
	}
	if (sqlite_saver.is_valid()) {
		ResourceSaver::remove_resource_format_saver(sqlite_saver);
		sqlite_saver.unref();
	}
}
