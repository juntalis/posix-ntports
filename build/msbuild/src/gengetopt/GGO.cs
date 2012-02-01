using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Reflection;
using Microsoft.Build.Framework;
using Microsoft.Build.Utilities;
using System.IO;
using Common;

namespace MSBuild.GenGetOpt
{
	public class GGO : Task
	{

		private string outputPath = string.Empty;

		[DefaultValue(false)]
		public bool Overwrite { get; set; }

		[Required]
		[FileExists]
		public string Include { get; set; }

		[DefaultValue(@"")]
		public string GGODir { get; set; }

		[DefaultValue(@"cmdline_parser")]
		public string Function { get; set; }

		[DefaultValue(@"gengetopt_args_info")]
		public string Struct { get; set; }

		[DefaultValue(@"")]
		public string Output { get; set; }

		[DefaultValue(@"")]
		public string OutputDir { get; set; }

		[DefaultValue(@"")]
		public string OutputExt { get; set; }

		[DefaultValue(false)]
		public bool LongHelp { get; set; }

		[DefaultValue(false)]
		public bool DefaultOptional { get; set; }

		[DefaultValue(@"")]
		public string UnNamedArgs { get; set; }

		[DefaultValue(false)]
		public bool StrParser { get; set; }

		[DefaultValue(false)]
		public bool ConfParser { get; set; }

		[DefaultValue(true)]
		public bool IncludeGetOpt { get; set; }

		[DefaultValue(false)]
		public bool NoHelp { get; set; }

		[DefaultValue(false)]
		public bool NoVersion { get; set; }

		[DefaultValue(false)]
		public bool NoError { get; set; }

		[DefaultValue(@"")]
		public string Version { get; set; }

		[DefaultValue(@"")]
		public string PackageName { get; set; }

		public GGO()
		{
			DefaultValueHelper.InitializeDefaultValues(this);
		}

		private void generateDefaultVars()
		{
			string sourceExt = "c";
			if (String.IsNullOrWhiteSpace(Output)) Output = Path.GetFileNameWithoutExtension(Include);
			if (String.IsNullOrWhiteSpace(OutputDir)) OutputDir = Path.GetDirectoryName(Include);
			if (!String.IsNullOrWhiteSpace(OutputExt)) sourceExt = OutputExt;
			if (String.IsNullOrWhiteSpace(GGODir)) {
				GGODir = Environment.GetEnvironmentVariable("GGODir") ??
					Path.GetDirectoryName(Assembly.GetAssembly(typeof(GGO)).Location);
			}
			// ReSharper disable AssignNullToNotNullAttribute
			outputPath = Path.Combine(OutputDir, String.Format("{0}.{1}", Output, sourceExt));
			// ReSharper restore AssignNullToNotNullAttribute
		}

		public override bool Execute()
		{
			generateDefaultVars();
			if (!Overwrite && File.Exists(outputPath)) {
				Log.LogMessage("File \"{0}\" exists and overwrite is false. Skipping.", outputPath);
				return true;
			}
			List<string> argList = new List<string> { String.Format("--input={0}", Include) };
			if (!String.IsNullOrWhiteSpace(Function)) argList.Add(String.Format("--func-name={0}", Function));
			if (!String.IsNullOrWhiteSpace(Struct)) argList.Add(String.Format("--arg-struct-name={0}", Struct));
			if (!String.IsNullOrWhiteSpace(Output)) argList.Add(String.Format("--file-name=={0}", Output));
			if (!String.IsNullOrWhiteSpace(OutputDir)) argList.Add(String.Format("--output-dir={0}", OutputDir));
			if (!String.IsNullOrWhiteSpace(OutputExt)) argList.Add(String.Format("--c-extension={0}", OutputExt));
			if (LongHelp) argList.Add("--long-help");
			if (DefaultOptional) argList.Add("--default-optional");
			if (!String.IsNullOrWhiteSpace(UnNamedArgs))
				argList.Add(
							UnNamedArgs.ToLower().Equals("true")
								? String.Format("-u")
								: String.Format("--unamed-opts={0}", UnNamedArgs));
			if (ConfParser) argList.Add("-C");
			if (StrParser) argList.Add("-S");
			if (IncludeGetOpt) argList.Add("-G");
			if (NoHelp) argList.Add("-n");
			if (NoVersion) argList.Add("-N");
			if (NoError) argList.Add("-e");
			if (!String.IsNullOrWhiteSpace(PackageName)) argList.Add(String.Format("--set-package={0}", PackageName));
			if (!String.IsNullOrWhiteSpace(Version)) argList.Add(String.Format("--set-version={0}", Version));

			ProcessStartInfo startInfo = new ProcessStartInfo(Path.GetFullPath(Path.Combine(GGODir, "gengetopt.exe"))) {
				CreateNoWindow = false,
				RedirectStandardOutput = true,
				RedirectStandardInput = true,
				RedirectStandardError = true,
				UseShellExecute = false
			};

			startInfo.WorkingDirectory = Path.GetDirectoryName(Include);
			string args = String.Empty;
			foreach (string arg in argList) args += arg.Contains(" ") ? String.Format("\"{0}\" ", arg) : arg + " ";
			startInfo.Arguments = args.Remove(args.Length - 1, 1);

			Log.LogCommandLine(startInfo.FileName + " " + startInfo.Arguments);
			Process ggoProc = Process.Start(startInfo);
			string stderr = ggoProc.StandardError.ReadToEnd();
			ggoProc.WaitForExit();

			if (ggoProc.ExitCode != 0) {
				Log.LogError("GenGetOpt ended with a non-zero return code.");
				Log.LogError(stderr);
			} else {
				Log.LogMessage("{0} generated successfully.", outputPath);
			}
			return !Log.HasLoggedErrors;
		}
	}
}
