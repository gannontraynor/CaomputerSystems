// mycopy.c
//Gannon Traynor
/* mycopy utility
 * makes a copy of a file and assigns the same file
 * permissions to the copy
 * Usage:
 *   ./mycopy <name of original file> <name of copy>
 * If the original file does not exist or the user
 * lacks permission to read it, mycopy emits an error.
 * Also, if a file or directory exists with the name
 * proposed for the copy, mycopy emits an error and
 * terminates.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int error( char * msg )
{
	perror( msg );
	return 2;
}

int usage( char * name )
{
	printf( "Usage: %s <file to copy> <name of copy>\n", name );
	return 1;
}
	
int main( int argc, char * argv[] )
{
	if ( argc != 3 )
		return usage( argv[0] );
	int file= open( argv[1], O_RDONLY, 0 );
	if ( file == -1 )
		return error( "file does not exist" );

	struct stat stat_struct;
	if ( fstat( file, &stat_struct ) == -1 )
		return error( "file was already created" );	
	mode_t permissions= stat_struct.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);
	
	int copy= open( argv[2], O_WRONLY|O_CREAT|O_EXCL, permissions );
	if ( copy == -1 )
		return error( "creating copy" );
	
	char buffer[BUFFER_SIZE];
	int bytes_read;
	int bytes_written;
	do
	{
		bytes_read= read( file, buffer, BUFFER_SIZE );
		if ( bytes_read > 0 )
			bytes_written= write( copy, buffer, bytes_read );
		if ( bytes_written < 1 )
			error( "write" );
	} 	while ( bytes_read > 0 );

	if ( bytes_read == -1 )
		error( "read" );
			
	close( file );
	close( copy );
	return 0;
}
