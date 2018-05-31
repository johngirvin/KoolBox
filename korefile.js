let project = new Project('k007');

project.addFile('Sources/**');
project.addIncludeDir('Sources');
project.addIncludeDir('Sources/KoolBox');
project.addIncludeDir('Sources/KoolBox/Camera');
project.addIncludeDir('Sources/KoolBox/Core');
project.addIncludeDir('Sources/KoolBox/Graphics');
project.addIncludeDir('Sources/KoolBox/Vendor');
project.addIncludeDir('Sources/Scenes/');
project.setDebugDir('Deployment');

resolve(project);
