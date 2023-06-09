/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2008-2015 Hellground <http://hellground.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef HELLGROUND_DATABASEENV_H
#define HELLGROUND_DATABASEENV_H

#include "Common.h"
#include "Log.h"

#include "Database/Field.h"
#include "Database/QueryResult.h"
#include "Database/QueryResultMysql.h"
#include "Database/Database.h"
#include "Database/DatabaseMysql.h"
typedef DatabaseMysql DatabaseType;

#define _LIKE_           "LIKE"
#define _TABLE_SIM_      "`"
#define _CONCAT3_(A,B,C) "CONCAT( " A " , " B " , " C " )"
#define _OFFSET_         "LIMIT %d,1"

extern HELLGROUND_IMPORT_EXPORT DatabaseType GameDataDatabase;
extern HELLGROUND_IMPORT_EXPORT DatabaseType RealmDataDatabase;
extern HELLGROUND_IMPORT_EXPORT DatabaseType AccountsDatabase;

#endif
