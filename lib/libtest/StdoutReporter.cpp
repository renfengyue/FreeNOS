/*
 * Copyright (C) 2015 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <ListIterator.h>
#include <TerminalCodes.h>
#include "TestCase.h"
#include "StdoutReporter.h"

StdoutReporter::StdoutReporter(int argc, char **argv)
    : TestReporter(argc, argv)
{
}

void StdoutReporter::reportBefore(TestInstance & test)
{
    printf("%s: %s .. ", basename(m_argv[0]), test.m_name);
}

void StdoutReporter::reportAfter(TestResult & result)
{
    switch (result)
    {
        case OK:   printf("%sOK\r\n", GREEN); break;
        case FAIL: printf("%sFAIL\r\n", RED); break;
        case SKIP: printf("%sSKIP\r\n", YELLOW); break;
    }
    printf("%s", WHITE);
}

void StdoutReporter::reportFinish()
{
    if (m_showStatistics)
    {
        if (m_fail)
            printf("%s: %sFAIL%s   ", basename(m_argv[0]), RED, WHITE);
        else
            printf("%s: %sOK%s   ", basename(m_argv[0]), GREEN, WHITE);

        printf("(%d passed %d failed %d skipped %d total)\r\n",
                m_ok, m_fail, m_skip, (m_ok + m_fail + m_skip));
    }

#ifdef __HOST__
    fflush(stdout);
#endif /* __HOST__ */
}
