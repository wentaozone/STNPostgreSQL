//
//  STNPostgreSQLStatement.h
//  STNPostgreSQL
//
//  Created by Simon Stiefel on 01.04.07.
//  Copyright 2007 stiefels.net. All rights reserved.
//
//  $Id$
//
//  Redistribution and use in source and binary forms, with or
//  without modification, are permitted provided that the
//  following conditions are met:
//
//  1. Redistributions of source code must retain the above
//  copyright notice, this list of conditions and the following
//  disclaimer.
//
//  2. Redistributions in binary form must reproduce the above
//  copyright notice, this list of conditions and the following
//  disclaimer in the documentation and/or other materials
//  provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
//  WARRANTIES, INCLUDING, BUT NOTLIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
//  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
//  OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
//  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
//  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <Cocoa/Cocoa.h>
#import "STNPostgreSQLConnection.h"
#import "STNPostgreSQLResult.h"
#import "STNPostgreSQLErrorField.h"

@interface STNPostgreSQLStatement : NSObject {
    NSString *_statement;
    STNPostgreSQLConnection *_connection;
    STNPostgreSQLConnection *_temporaryConnection;
    STNPostgreSQLResult *_result;
    id _delegate;
}

+ (STNPostgreSQLStatement *)statement;
+ (STNPostgreSQLStatement *)statementWithConnection:(STNPostgreSQLConnection *)connection;
+ (STNPostgreSQLStatement *)statementWithStatement:(NSString *)statement;
+ (STNPostgreSQLStatement *)statementWithConnection:(STNPostgreSQLConnection *)connection andStatement:(NSString *)statement;

- (id)initWithConnection:(STNPostgreSQLConnection *)connection;

- (void)setStatement:(NSString *)statement;
- (NSString *)statement;

- (void)setDelegate:(id)delegate;
- (id)delegate;

- (void)setConnection:(STNPostgreSQLConnection *)connection;
- (STNPostgreSQLConnection *)connection;
- (STNPostgreSQLConnection *)primaryConnection;

- (BOOL)execute:(NSError **)error;
- (BOOL)executeWithConnection:(STNPostgreSQLConnection *)connection error:(NSError **)error;
- (void)startExecution;
- (void)startExecutionWithConnection:(STNPostgreSQLConnection *)connection;
- (void)executeWithDelegateCalls:(id)param;

- (STNPostgreSQLResult *)result;

- (STNPostgreSQLErrorField *)generateErrorField:(PGresult *)result;

@end

@interface NSObject (STNPostgreSQLStatementDelegateMethods)
- (BOOL)executionAttemptShouldStart;
- (void)executionAttemptWillStart;
- (void)executionAttemptEnded:(BOOL)success error:(NSError *)error;
@end
