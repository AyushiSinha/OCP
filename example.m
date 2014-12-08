% Download cube of data
fprintf('Downloading cube... ' ) ;
oo = OCP();
oo.setServerLocation('http://braingraph1dev.cs.jhu.edu');
oo.setImageToken('kasthuri11cc');

q = OCPQuery;
q.setType(eOCPQueryType.annoDense);

q.setXRange([4400,5424]);
q.setYRange([5440,6464]);
q.setZRange([1100,1200]);
q.setResolution(1);
q.setType(eOCPQueryType.imageDense);
imageAC4 = oo.query(q);
fprintf('Done.\n' ) ;

fprintf('Finding reticula... ' ) ;
% Allocate space for ourput cube
out = zeros(size(imageAC4.data));

% Find Reticula per slice 
FindReticula( '--in', double(imageAC4.data), '--out' ,out, '--axoplasmicreticula');
fprintf('Done.\n' ) ;

% Compute connected components to find Reticula strands
fprintf('Computing connected components... ' ) ;
CC = bwconncomp( out , 26 ) ;
rp = regionprops(CC,'PixelIdxList');
fprintf( 'Done. Number of connected components = %d.\n' , length(rp) ) ;

fprintf('Initializing upload... ' ) ;
E = RAMONVolume;
E.setXyzOffset([4400,5440,1100]);
oo.setImageToken('kasthuri11cc');

% Use token name for your database
oo.setAnnoToken('kat11_ayushi_AR10'); 
fprintf('Done.\n' ) ;

fprintf('Uploading annotations...\n' ) ;
for i = 1:length(rp)
    if mod(i,1000) == 0
        fprintf('%f%% Complete...\n' , i*100/length(rp) ) ;
    end
    
    clear pixLoc    
    q = rp(i).PixelIdxList ;
    [pixLoc(:,2),pixLoc(:,1),pixLoc(:,3)] = ind2sub(CC.ImageSize,q);
    
    AR = RAMONOrganelle;
    AR.setClass(eRAMONOrganelleClass.axoplasmicReticula);
    AR.setResolution(1);
    
    % Pick relevant author name for your upload
    AR.setAuthor('Ayushi_ReticulaUpload_December14');

    AR.setVoxelList(E.local2Global(pixLoc));
    oo.createAnnotation(AR); 
end
fprintf('Done.\n') ;