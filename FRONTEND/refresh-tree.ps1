$root='d:\CSE\4th sem\OS\OS'
$outJs='d:\CSE\4th sem\OS\OS\FRONTEND\fs-tree.js'
$outJson='d:\CSE\4th sem\OS\OS\FRONTEND\fs-tree.json'
$textExt=@('.c','.h','.cpp','.sh','.txt','.md','.js','.css','.html','.json','.yml','.yaml','.py')
function NewDir { [ordered]@{ type='dir'; children=[ordered]@{} } }
$tree=NewDir
Get-ChildItem -LiteralPath $root -Recurse -Force | ForEach-Object {
  $full=$_.FullName
  if($full -like "$root\FRONTEND\*" -or $full -like "$root\.git\*"){ return }
  $rel=$full.Substring($root.Length).TrimStart('\\')
  if([string]::IsNullOrWhiteSpace($rel) -or $rel -eq 'FRONTEND' -or $rel -eq '.git'){ return }
  $parts=$rel -split '\\'
  $node=$tree
  for($i=0;$i -lt $parts.Length;$i++){
    $part=$parts[$i]
    $last=($i -eq $parts.Length-1)
    if($last){
      if($_.PSIsContainer){
        if(-not $node.children.Contains($part)){ $node.children[$part]=NewDir }
      } else {
        $ext=[IO.Path]::GetExtension($part).ToLowerInvariant()
        $isBinary = -not ($textExt -contains $ext)
        $node.children[$part]=[ordered]@{ type='file'; binary=$isBinary }
      }
    } else {
      if(-not $node.children.Contains($part)){ $node.children[$part]=NewDir }
      $node=$node.children[$part]
    }
  }
}
$json=$tree | ConvertTo-Json -Depth 100 -Compress
Set-Content -LiteralPath $outJs -Value ("export const fsTree = " + $json + ";") -Encoding UTF8
Set-Content -LiteralPath $outJson -Value $json -Encoding UTF8
Write-Output "Tree refreshed"
